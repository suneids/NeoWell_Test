#include "config.h"

#define SAMPLES 128u

static uint16_t saw[2][SAMPLES];
const SCPI_CommandDef commands[] = {
	{"*IDN",           CMD_IDN,        SCPI_QUERY,   SCPI_ARG_NONE},

	{"SOUR:FREQ",      CMD_FREQ_SET,   SCPI_COMMAND, SCPI_ARG_REQUIRED},
	{"SOUR:FREQ",      CMD_FREQ_GET,   SCPI_QUERY,   SCPI_ARG_NONE},

	{"SOUR:VOLT",      CMD_AMPL_SET,   SCPI_COMMAND, SCPI_ARG_REQUIRED},
	{"SOUR:VOLT",      CMD_AMPL_GET,   SCPI_QUERY,   SCPI_ARG_NONE},

	{"SOUR:VOLT:OFFS", CMD_OFFSET_SET, SCPI_COMMAND, SCPI_ARG_REQUIRED},
	{"SOUR:VOLT:OFFS", CMD_OFFSET_GET, SCPI_QUERY,   SCPI_ARG_NONE},

	{"OUTP",           CMD_OUTPUT_SET, SCPI_COMMAND, SCPI_ARG_REQUIRED},
	{"OUTP",           CMD_OUTPUT_GET, SCPI_QUERY,   SCPI_ARG_NONE},

	{"SYST:STAT",      CMD_STATUS_GET, SCPI_QUERY,   SCPI_ARG_NONE},
	{"STATUS", 		   CMD_STATUS_GET, SCPI_QUERY,   SCPI_ARG_NONE},
	{"SYST:HELP",      CMD_HELP_GET,   SCPI_QUERY,   SCPI_ARG_NONE},
	{"HELP", 		   CMD_HELP_GET,   SCPI_QUERY  , SCPI_ARG_NONE},
	{"SOUR:VALUE",     CMD_VALUE_GET,  SCPI_QUERY,   SCPI_ARG_NONE}
};

uint32_t registers[REG_COUNT] = {
	    [REG_FREQ]   = SAW_FREQ_HZ,
	    [REG_AMPL]   = AMPL_MV,
	    [REG_OFFSET] = OFFSET_MV,
	    [REG_OUTPUT] = 1u
};

uint16_t uart_cfg = 4u;
// Индекс 4 = 115200 бод в моей HAL
// Parity = 0, Stop bits = 1
SCPI_cfg scpi_cfg = {
    .USARTx = USART1,
    .uart_cfg_reg = &uart_cfg,
    .available_commands = commands,
    .command_count = sizeof(commands) / sizeof(commands[0])
};

static uint8_t saw_update_state = SAW_READY;
static uint8_t saw_dirty = 0;
static volatile uint8_t saw_dma_events = 0;

static void SAW_DMACallback(DMA_Event_t event){
    if (event == DMA_EVENT_HT) saw_dma_events |= 0x01u;
    if (event == DMA_EVENT_TC) saw_dma_events |= 0x02u;
}

void SAW_Init(void){
    GPIO_PinMode((GPIO_Pin_t){ .port = GPIOA, .number = 4,  .moder = GPIO_MODE_ANALOG, .pull = GPIO_NOPULL});

    SAW_Build();
    uint32_t tim_clk = RCC_GetTIMPclk1_Hz();
    uint32_t psc = 1u;

    uint32_t arr = tim_clk /((psc + 1u) * SAMPLES * SAW_FREQ_HZ) - 1u;

    TIM_Init(TIM6, psc, arr, 0);
    TIM_Stop(TIM6);
    TIM_SetTRGOUpdate(TIM6);

    DAC_Init();
    DAC_SetTrigger(DAC_CHANNEL_1, DAC_TRIGGER_TIM6);
    DAC_EnableDMA(DAC_CHANNEL_1);

    DMA_Init(DMA1_Channel1, (uint32_t)&DAC1->DHR12R1, (uint32_t)&saw[0][0], 2u * SAW_SAMPLES);
    DMA_SetHandler(DMA1_Channel1, SAW_DMACallback);
    TIM_Start(TIM6);
}



static void SAW_BuildHalf(uint8_t half) {
    uint32_t ampl = registers[REG_AMPL];
    uint32_t offset = registers[REG_OFFSET];

    uint32_t min_mv = offset - ampl;
    uint32_t span_mv = 2u * ampl;

    for (uint32_t i = 0; i < SAW_SAMPLES; i++) {
        uint32_t mv = min_mv + span_mv * i / (SAW_SAMPLES - 1u);

        saw[half][i] = (uint16_t)(mv * 4095u / VDDA_MV);
    }
}

void SAW_Build(void) {
    SAW_BuildHalf(0);
    SAW_BuildHalf(1);
}



void SAW_SetFrequency(uint32_t freq) {
    uint32_t tim_clk = RCC_GetTIMPclk1_Hz();
    uint32_t psc = TIM6->PSC + 1u;

    uint32_t arr = tim_clk / (psc * SAW_SAMPLES * freq) - 1u;

    TIM6->ARR = arr;
}


static uint8_t ParseU32(const char *str, uint32_t *result) {
    if (*str < '0' || *str > '9') return 0;

    char *end;
    unsigned long value = strtoul(str, &end, 10);

    if (*end != '\0' || value > UINT32_MAX) return 0;

    *result = (uint32_t)value;
    return 1;
}


static uint8_t ParseVolts(const char *str, uint32_t *result) {
    if (*str < '0' || *str > '9') return 0;

    char *end;
    unsigned long whole = strtoul(str, &end, 10);

    if (whole > VDDA_MV / 1000u) return 0;

    uint32_t mv = (uint32_t)whole * 1000u;

    if (*end == '.') {
        end++;
        uint32_t factor = 100u;

        if (*end < '0' || *end > '9') return 0;

        while (*end >= '0' && *end <= '9') {
            if (factor == 0) return 0;

            mv += (uint32_t)(*end - '0') * factor;
            factor /= 10u;
            end++;
        }
    }

    if (*end != '\0' || mv > VDDA_MV) return 0;

    *result = mv;
    return 1;
}


void DEVICE_Analyyze(){
	SCPI_ParsedCommand cmd;
	while (SCPI_PopCommand(&cmd)){
		char response[64];
		switch (cmd.id){

			case CMD_IDN: {
				const char responseIDN[] = "NeoWell_Test,STM32G0B1,SAW,0.1\r\n";
				SCPI_Write(responseIDN, sizeof(responseIDN) - 1u);
				break;
			}

			case CMD_FREQ_GET:{
			    snprintf(response, sizeof(response), "%lu\r\n", (unsigned long)registers[REG_FREQ]);
			    SCPI_Write(response, strlen(response));
			    break;
			}

			case CMD_AMPL_GET:{
			    snprintf(response, sizeof(response), "%lu.%03lu\r\n", (unsigned long)(registers[REG_AMPL] / 1000u), (unsigned long)(registers[REG_AMPL] % 1000u));
			    SCPI_Write(response, strlen(response));
			    break;
			}

			case CMD_OFFSET_GET:{
			    snprintf(response, sizeof(response), "%lu.%03lu\r\n", (unsigned long)(registers[REG_OFFSET] / 1000u),  (unsigned long)(registers[REG_OFFSET] % 1000u));
			    SCPI_Write(response, strlen(response));
			    break;
			}

			case CMD_OUTPUT_GET:{
			    SCPI_Write(registers[REG_OUTPUT] ? "1\r\n" : "0\r\n", 3);
			    break;
			}

			case CMD_FREQ_SET: {
			    uint32_t value;

			    if (!ParseU32(cmd.value, &value) ||
			        value < 1u || value > 1000u) {
			        SCPI_Write("ERR:VALUE\r\n", 11);
			        break;
			    }

			    SAW_SetFrequency(value);
			    registers[REG_FREQ] = value;

			    SCPI_Write("OK\r\n", 4);
			    break;
			}



			case CMD_AMPL_SET: {
			    uint32_t value;

			    if (!ParseVolts(cmd.value, &value) ||
			        value > registers[REG_OFFSET] ||
			        value > VDDA_MV - registers[REG_OFFSET]) {
			        SCPI_Write("ERR:VALUE\r\n", 11);
			        break;
			    }

			    registers[REG_AMPL] = value;
			    SCPI_Write("OK\r\n", 4);
			    break;
			}

			case CMD_OFFSET_SET: {
			    uint32_t value;

			    if (!ParseVolts(cmd.value, &value) ||
			        value < registers[REG_AMPL] ||
			        value > VDDA_MV - registers[REG_AMPL]) {
			        SCPI_Write("ERR:VALUE\r\n", 11);
			        break;
			    }

			    registers[REG_OFFSET] = value;
			    SCPI_Write("OK\r\n", 4);
			    break;
			}

			case CMD_OUTPUT_SET: {
			    if (!strcmp(cmd.value, "ON") || !strcmp(cmd.value, "1")) {
			        registers[REG_OUTPUT] = 1u;
			    }
			    else if (!strcmp(cmd.value, "OFF") || !strcmp(cmd.value, "0")) {
			        registers[REG_OUTPUT] = 0u;
			    }
			    else {
			        SCPI_Write("ERR:VALUE\r\n", 11);
			        break;
			    }

			    SCPI_Write("OK\r\n", 4);

			    if (registers[REG_OUTPUT]) TIM_Start(TIM6);
			    else TIM_Stop(TIM6);

			    break;
			}

			case CMD_HELP_GET: {
			    const char help[] = "*IDN?\r\n"
			    				     "SOUR:FREQ <Hz> | SOUR:FREQ?\r\n"
									 "SOUR:VOLT <V> | SOUR:VOLT?\r\n"
								 	 "SOUR:VOLT:OFFS <V> | SOUR:VOLT:OFFS?\r\n"
									 "OUTP ON|OFF | OUTP?\r\n"
			    					 "SYST:STAT?\r\n"
			    					 "SOUR:VALUE?\r\n"
									 "SYST:HELP?\r\n";

			    SCPI_Write(help, sizeof(help) - 1u);
			    break;
			}

			case CMD_STATUS_GET: {
			    int len = snprintf(response, sizeof(response),
			        "FREQ=%lu Hz\r\n"
			        "AMPL=%lu.%03lu V\r\n"
			        "OFFSET=%lu.%03lu V\r\n"
			        "OUTPUT=%s\r\n",
			        (unsigned long)registers[REG_FREQ],
			        (unsigned long)(registers[REG_AMPL] / 1000u),
			        (unsigned long)(registers[REG_AMPL] % 1000u),
			        (unsigned long)(registers[REG_OFFSET] / 1000u),
			        (unsigned long)(registers[REG_OFFSET] % 1000u),
			        registers[REG_OUTPUT] ? "ON" : "OFF"
			    );

			    if (len > 0 && (size_t)len < sizeof(response))
			        SCPI_Write(response, (uint16_t)len);

			    break;
			}
			case CMD_VALUE_GET:{
			    snprintf(response, sizeof(response), "%lu\r\n", (unsigned long)DAC1->DOR1);

			    SCPI_Write(response, strlen(response));
			    break;
			}
			default:
				break;
		}
	}
}
