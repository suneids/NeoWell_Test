#include "config.h"

#define SAMPLES 128u

static uint16_t saw[SAMPLES];

void BuildSaw(void){
    for(uint32_t i = 0; i < SAMPLES; i++){
        uint32_t mv = 500u + 2000u * i / (SAMPLES - 1u);
        saw[i] = (uint16_t)(mv * 4096u / 3300u);
    }
}

void Saw_Init(void){
    GPIO_PinMode((GPIO_Pin_t){ .port = GPIOA, .number = 4,  .moder = GPIO_MODE_ANALOG, .pull = GPIO_NOPULL});

    BuildSaw();

    uint32_t tim_clk = RCC_GetTIMPclk1_Hz();
    uint32_t arr = tim_clk / (SAMPLES * 100u) - 1u;

    TIM_Init(TIM6, 0, arr, 0);
    TIM_Stop(TIM6);
    TIM_SetTRGOUpdate(TIM6);

    DAC_Init();
    DAC_SetTrigger(DAC_CHANNEL_1, DAC_TRIGGER_TIM6);
    DAC_EnableDMA(DAC_CHANNEL_1);

    DMA_Init(DMA1_Channel1, (uint32_t)&DAC1->DHR12R1, (uint32_t)saw, SAMPLES);

    TIM_Start(TIM6);
}
