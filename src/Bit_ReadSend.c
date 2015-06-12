#include "Bit_ReadSend.h"

/*	Description:    Send single bit
 *
 *                  Write MODE
 *                  ==========
 *                  - HOST send bit on falling edge
 *                  - TARGET read on next rising edge
 *
 *                  Read MODE
 *                  ==========
 *                  - HOST read on next falling edge
 *                  - TARGET send bit on rising edge
 *
 *                  SWDIO will set high when data is 1
 *                  SWDIO will set low when data is 0
 *
 *	Parameters:     value is the single bit data
 *
 *  Return:         none
 */
void sendBit(int value)
{
	SWCLK_OFF();

	if(value == 1)
		SWDIO_High();
	else
		SWDIO_Low();

	SWCLK_ON();
}

/*	Description:    Send multiple bits !*Send LSB First*!
 *                  - SWDIO will set high when data is not 0
 *                  - SWDIO will set low when data is 0
 *
 *	Parameters:     dataToSend is the data ready to send
 *                  numberOfBits is the number of bit need to send
 *
 *  Returns:        NONE
 */
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

/*	Description:    Read single bit
 *
 *                  Write MODE
 *                  ==========
 *                  - HOST send bit on falling edge
 *                  - TARGET read on next rising edge
 *
 *                  Read MODE
 *                  ==========
 *                  - HOST read on next falling edge
 *                  - TARGET send bit on rising edge
 *
 *                  SWDIO will set high when data is not zero
 *                  SWDIO will set low when data is zero
 *
 *	Parameters:     dataToSend is the data ready to send
 *                  numberOfBits is the number of bit need to send
 *
 *  Returns:        readSWDIO_Pin bit status on the SWDIO_PIN
 */
int readBit()
{
	SWCLK_ON();
	SWCLK_OFF();

	return readSWDIO_Pin();
}

/*	Description:    Read multiple bits !*Read LSB First*!
 *
 *	Parameters:     dataRead is the data need to be read
 *                  numberOfBits is to declare how many bits need to be read
 *
 *  Returns:        NONE
 */
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
