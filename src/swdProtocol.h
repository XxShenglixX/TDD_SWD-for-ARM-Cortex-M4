#ifndef swdProtocol_H
#define swdProtocol_H

#include "Bit_ReadSend.h"
#include "ClkAndIO_Control.h"
#include "configurePort.h"
#include "Reset.h"

//SWD_Sequence
#define	STARTBIT 1
#define	STOPBIT 0
#define	PARKBIT 1
#define READ 1
#define WRITE 0
#define DP 0
#define AP 1

typedef enum
{
	STICKYORUN ,
	WDATAERR,
	STICKYERR,
	STICKYCMP
} ErrorFlag ;

typedef enum
{
	OK = 1,
	WAIT = 2,
	FAULT = 4,
	WAITED_TOOLONG = 5
} ACK_Response;


void initialisation();
void sendSWDRequest(int SWD_RequestData);
void switchJTAGtoSWD();
int SWD_Request(int APnDP,int ReadWrite,int Address);
int check_SWDRequest_Parity(int APnDP, int RnW, int addrBit3, int addrBit2);
int check_32bits_Data_Parity(uint32_t Data,int *Parity);
int checkAddressbit(int address,int bitNumber);

//int checkACK_RWData(uint32_t *data,int *Parity, int SWD_RequestData, int ReadWrite);
//int retryCurrentOperation(uint32_t *data,int *Parity, int SWD_RequestData, int ReadWrite);
//void Read_32bits_Data_Parity(uint32_t  *data,int *Parity);
//void switchOutput_Send_32bits_Data_Parity(uint32_t *data,int *Parity);
//int AP_Select(int APnDP,int BankNo,int APSEL);
//int ABORT_CLEAR_ERRFLAG(int DAPabort,ErrorFlag errflag);

#endif // swdProtocol_H
