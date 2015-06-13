#include "Reset.h"
#include "Delay.h"
#include "ClkAndIO_Control.h"

void resetTarget()
{
	ResetPin_Low();
	delay(500,1,1);
	ResetPin_High();
	delay(2600,1,1);
}

void lineReset()
{
	int i ;

	SWDIO_High();
	for (i = 0 ; i < 53 ; i ++)
		clockGenerator_1cycle();
}
