#include "Bit_ReadSend.h"

/*	Send single bit during falling edge
 *	input : single bit data
 */
void sendBit(int value)
{
	SWCLK_OFF();

	if	(value == 1)
		SWDIO_High();
	else
		SWDIO_Low();

	SWCLK_ON();
}

void sendBits(uint32_t dataToSend,int numberOfBits)
{
	//LSB first
	int i , bitValue = 0;
	for (i = 0; i < numberOfBits; i ++)
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

/* Read multiple bits !*Read LSB First*!
 * input: 
 *        dataRead is the data need to be read
 *        numberOfBits is to declare how many bits need to be read
 * output:
 *        store data back into dataRead after read in LSB first form
 */
void readBits(uint32_t *dataRead,int numberOfBits)
{
	int i ;
	int bitRead = 0;

	for ( i = 0 ; i < numberOfBits ; i ++)
	{
		bitRead = readBit();
		*dataRead = *dataRead | (bitRead << i ) ;
    printf("dataRead %d ", *dataRead);
	}

}
