
#include <stdint.h>
#include "../Inc/inc/mcu_config.h"
#include "../Inc/inc/tim.h"
#include "../Inc/inc/gpio.h"
#include "../Inc/inc/tim.h"
#include "../Inc/inc/dma.h"
#include "../Inc/inc/dac.h"

#define SAW_SAMPLES 128u
#define SAW_FREQ_HZ 100u
#define VDDA_MV     3300u
#define AMPL_MV     1000u
#define OFFSET_MV   1500u

#define DAC_DMA_CH  DMA1_Channel1


void BuildSaw(void);
void Saw_Init(void);
