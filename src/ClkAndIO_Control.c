#include "ClkAndIO_Control.h"

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
	return HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_12);
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