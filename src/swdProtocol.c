#include "swdProtocol.h"

void initialisation()
{
	int SWD_RequestData, ACK = 0;
	int Parity = 0 ;
	uint32_t IDCODE = 0;

	SWD_RequestData = SWD_Request(DP,READ,0x00);

	//resetTarget();
	SWDIO_LowHigh();
	switchJTAGtoSWD();

	sendSWDRequest(SWD_RequestData);
	readBits((uint32_t *)&ACK,3);
	readBits(&IDCODE,32);
	Parity = readBit();

	//Eight extra idle clock
	extraIdleClock(8);
	lineReset();
}

void sendSWDRequest(int SWD_RequestData)
{
	sendBits(SWD_RequestData,8);
	turnAround();
	SWDIO_InputMode();

}

/* To switch SWJ-DP from JTAG to SWD operation:
 * 1. Send more than 50 SWDCLK cycles with SWDIO = 1. This ensures that both SWD and JTAG are in their reset states
 * 2. Send the 16-bit (0xE79E LSB first) JTAG-to-SWD select sequence on SWDIO
 * 3. Send more than 50 SWDCLK cycles with SWDIO = 1. This ensures that if SWJ-DP was already in SWD mode.
 * 4. Send two or more SWDCLK cycles with SWDIO = 0. This ensures that the SWD line is in the idle state
 *    before starting a new SWD packet transaction.
 */
void switchJTAGtoSWD()
{
	lineReset();
	sendBits(0xE79E,16);
	lineReset();

	extraIdleClock(3);
}


int SWD_Request(int APnDP,int ReadWrite,int Address)
{
	int SWD_RequestData = 0;
	int Address_bit2 , Address_bit3, ParityBit ;

	Address_bit2 = checkAddressbit(Address,2);
	Address_bit3 = checkAddressbit(Address,3);

	ParityBit = check_SWDRequest_Parity(APnDP,ReadWrite,Address_bit3,Address_bit2);

	SWD_RequestData = SWD_RequestData | STARTBIT << 0 ;
	SWD_RequestData = SWD_RequestData | APnDP << 1 ;
	SWD_RequestData = SWD_RequestData | ReadWrite << 2 ;
	SWD_RequestData = SWD_RequestData | Address_bit2 << 3;
	SWD_RequestData = SWD_RequestData | Address_bit3 << 4;
	SWD_RequestData = SWD_RequestData | ParityBit << 5;
	SWD_RequestData = SWD_RequestData | STOPBIT << 6;
	SWD_RequestData = SWD_RequestData | PARKBIT << 7 ;

	return SWD_RequestData ;
}

int checkACK_RWData(uint32_t *data,int *Parity, int SWD_RequestData, int ReadWrite)
{
	int ACK  = 0, status = 0;
	readBits((uint32_t *)&ACK,3);

	if (ACK == OK)
	{
		if (ReadWrite)
			Read_32bits_Data_Parity(data,Parity);
		else
			switchOutput_Send_32bits_Data_Parity(data,Parity);

		return OK ;
	}
	else if (ACK == WAIT)
	{
		status = retryCurrentOperation(data,Parity,SWD_RequestData,ReadWrite);
		return status ;
	}
	else
		return FAULT ; //FAULT response or no response
}

int check_SWDRequest_Parity(int APnDP, int RnW, int addrBit3, int addrBit2)
{
	int sum = 0;

	sum = APnDP + RnW + addrBit3 + addrBit2;

	if((sum % 2) != 0) //if odd num 1's return 1
		return 1;
	else return 0; // if even numm  1's return 0
}

int check_32bits_Data_Parity(uint32_t Data,int *Parity)
{
	int sum = 0 ;

	while (Data > 0)
	{
		if ( (Data & 1) == 1)
			sum ++ ;
		Data = Data >> 1;
	}

	if((sum % 2) != 0) //if odd num 1's return 1
			return 1;
	else return 0; // if even numm  1's return 0
}


int checkAddressbit(int address,int bitNumber)
{
	int address_bit =0 ;

	address_bit = address & ( 1 << bitNumber);

	if (address_bit !=0)
		return 1 ;
	else
		return 0 ;
}


int ABORT_CLEAR_ERRFLAG(int DAPabort,ErrorFlag errflag)
{
	unsigned long data = 0x00000000;
	int SWD_RequestData = 0 ;
	int status = 0 , Parity = 0;

	if (DAPabort == 1)
		data = data | DAPabort ;
	else
	{
		switch(errflag)
		{
			case	STICKYORUN :
								data = data | 1 << 4 ;
								break ;
			case	WDATAERR:
								data = data | 1 << 3 ;
								break ;
			case	STICKYERR:
								data = data | 1 << 2 ;
								break ;
			case	STICKYCMP:
								data = data | 1 << 1 ;
								break ;
		}
	}

	SWD_RequestData = SWD_Request(DP,WRITE,0x00);
	sendSWDRequest(SWD_RequestData);
	status = checkACK_RWData(&data,&Parity,SWD_RequestData,WRITE);

	return status ;
}

int AP_Select(int APnDP,int BankNo,int APSEL)
{
	unsigned long data = 0x00000000 ;
	int SWD_RequestData = 0 ;
	int status = 0 , Parity = 0;


	if (APnDP == DP) //debug port select modification
		data = data | (BankNo & 0x00000001) ; //modify bit 0
	else //access port select modification
	{
		if (BankNo == 0x0 || BankNo == 0x1 || BankNo == 0xF)
			data = data | BankNo << 4 ; //modify bit [7:4]
		else // unknown/non existing BankNo
			return 0 ;
	}

	SWD_RequestData = SWD_Request(DP,WRITE,0x08);
	sendSWDRequest(SWD_RequestData);
	status = checkACK_RWData(&data,&Parity,SWD_RequestData,WRITE);
	return status ;
}


int retryCurrentOperation(uint32_t *data,int *Parity, int SWD_RequestData, int ReadWrite)
{
	int i , ACK = 0  ;

	for ( i = 0 ; i < 3 ; i ++) //retry for maximum 3 times
	{
		sendSWDRequest(SWD_RequestData); // resend SWD request
		readBit(&ACK,3); // check ACK
		if (ACK == OK)
		{
			if (ReadWrite)
				Read_32bits_Data_Parity(data,Parity);
			else
				switchOutput_Send_32bits_Data_Parity(data,Parity);

			return OK ;
		}
	}
	return WAITED_TOOLONG ;

}

void switchOutput_Send_32bits_Data_Parity(uint32_t *data,int *Parity)
{
	SWDIO_OutputMode();
	clockGenerator_1cycle(); //turn around
	sendBits(*data,32);
	sendBits(*Parity,1);
}

void Read_32bits_Data_Parity(uint32_t *data,int *Parity)
{
	readBits(data,32);
	*Parity = readBit();
}

