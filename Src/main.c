#include <stdint.h>
#include "config.h"

int main(void)
{
	Clock64MHz_FromHSE();
	SAW_Init();
	SCPI_Init(&scpi_cfg);
	SCPI_Write("BOOT\r\n", 6);
	while(67){
		  SCPI_Process();
		  DEVICE_Analyyze();
		  SAW_Process();
	}
}
