#include "IO_Operations.h"

void clockGenerator_1cycle()
{
	SWCLK_OFF();
	SWCLK_ON();
}

/* include two IDLE clock cycles with SWDIO low for each packet
 * to ensure the operation is in stable mode
 */
void extraIdleClock(int numberOfClocks)
{
	int i;

	SWDIO_Low();
	for(i = 0 ; i < numberOfClocks ; i ++)
		clockGenerator_1cycle();
}

int readSWDIO_Pin()
{
	GPIO_PinState bitRead ;
	bitRead  = HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_12);

	return bitRead ;
}

void turnAround()
{
	SWCLK_OFF(); //turn around
}

void SWDIO_LowHigh()
{
	SWDIO_Low();
	SWDIO_High();
}