
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../Inc/inc/mcu_config.h"
#include "../Inc/inc/tim.h"
#include "../Inc/inc/gpio.h"
#include "../Inc/inc/tim.h"
#include "../Inc/inc/dma.h"
#include "../Inc/inc/dac.h"
#include "../Inc/inc/SCPI.h"
#define SAW_SAMPLES 128u
#define SAW_FREQ_HZ 1
#define VDDA_MV     3300u
#define AMPL_MV     1000u
#define OFFSET_MV   1500u

#define DAC_DMA_CH  DMA1_Channel1



enum {
    CMD_IDN = 1,

    CMD_FREQ_SET,
    CMD_FREQ_GET,

    CMD_AMPL_SET,
    CMD_AMPL_GET,

    CMD_OFFSET_SET,
    CMD_OFFSET_GET,

    CMD_OUTPUT_SET,
    CMD_OUTPUT_GET,

    CMD_STATUS_GET,
    CMD_HELP_GET,
    CMD_VALUE_GET
};


enum {
    REG_FREQ,
    REG_AMPL,
    REG_OFFSET,
    REG_OUTPUT,
    REG_COUNT
};


enum {
    SAW_READY = 0,
    SAW_WAIT_HT,
    SAW_WAIT_TC
};


extern const SCPI_CommandDef commands[];
extern uint32_t registers[REG_COUNT];

extern uint16_t uart_cfg;

extern SCPI_cfg scpi_cfg;



void SAW_Init(void);
void SAW_Build(void);
void SAW_SetFrequency(uint32_t freq);

void DEVICE_Analyyze();
