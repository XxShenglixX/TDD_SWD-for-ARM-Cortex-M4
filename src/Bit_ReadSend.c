#include "Bit_ReadSend.h"

void sendBit(int value)
{
	SWCLK_OFF() ;

	if (value == 1)
		SWDIO_High();
	else
		SWDIO_Low();

	SWCLK_ON();
}

void sendBits(uint32_t dataToSend,int numberOfBits)
{
	//LSB first
	int i , bitValue = 0;
	for (i=0 ; i < numberOfBits ; i ++)
	{
		bitValue = dataToSend & (1 << i ) ;

		if (bitValue != 0)
			sendBit(1);
		else
			sendBit(0);
	}

}

int readBit()
{
	int bitRead = 0 ;

	SWCLK_ON();
	//delay(3,1,10);
	SWCLK_OFF();

	bitRead = readSWDIO_Pin();
	return bitRead ;
}

void readBits(uint32_t *dataRead,int numberOfBits)
{
	int i ;
	int bitRead = 0;

	for ( i = 0 ; i < numberOfBits ; i ++)
	{
		bitRead = readBit();
		*dataRead = *dataRead | (bitRead << i ) ;
	}

}
