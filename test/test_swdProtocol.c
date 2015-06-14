#include "unity.h"
#include "Bit_ReadSend.h"
#include "mock_configurePort.h"
#include "mock_ClkAndIO_Control.h"
#include "mock_Delay.h"
#include "mock_Reset.h"
#include "swdProtocol.h"
#include <stdint.h>

void setUp(void)
{
}

void tearDown(void)
{
}


void test_switchJTAGtoSWD_should_call_lineReset_send0xE79E_lineReset_extraIdleClock()
{
	//0xE79E = 1110 0111 1001 1110

	int i = 0;

	lineReset_Expect();

	//E
	//send 0
	SWCLK_OFF_Expect();SWDIO_Low_Expect();SWCLK_ON_Expect();
	//send 1
	SWCLK_OFF_Expect();SWDIO_High_Expect();SWCLK_ON_Expect();
	//send 1
	SWCLK_OFF_Expect();SWDIO_High_Expect();SWCLK_ON_Expect();
	//send 1
	SWCLK_OFF_Expect();SWDIO_High_Expect();SWCLK_ON_Expect();

	//9
	//send 1
	SWCLK_OFF_Expect();SWDIO_High_Expect();SWCLK_ON_Expect();
	//send 0
	SWCLK_OFF_Expect();SWDIO_Low_Expect();SWCLK_ON_Expect();
	//send 0
	SWCLK_OFF_Expect();SWDIO_Low_Expect();SWCLK_ON_Expect();
	//send 1
	SWCLK_OFF_Expect();SWDIO_High_Expect();SWCLK_ON_Expect();

	//7
	//send 1
	SWCLK_OFF_Expect();SWDIO_High_Expect();SWCLK_ON_Expect();
	//send 1
	SWCLK_OFF_Expect();SWDIO_High_Expect();SWCLK_ON_Expect();
	//send 1
	SWCLK_OFF_Expect();SWDIO_High_Expect();SWCLK_ON_Expect();
	//send 0
	SWCLK_OFF_Expect();SWDIO_Low_Expect();SWCLK_ON_Expect();

	//E
	//send 0
	SWCLK_OFF_Expect();SWDIO_Low_Expect();SWCLK_ON_Expect();
	//send 1
	SWCLK_OFF_Expect();SWDIO_High_Expect();SWCLK_ON_Expect();
	//send 1
	SWCLK_OFF_Expect();SWDIO_High_Expect();SWCLK_ON_Expect();
	//send 1
	SWCLK_OFF_Expect();SWDIO_High_Expect();SWCLK_ON_Expect();

	lineReset_Expect();

	extraIdleClock_Expect(3);

	switchJTAGtoSWD();
}

void test_check_SWDRequest_Parity_should_return_1_if_input_0100()
{
	int Parity = 0 ;
	Parity = check_SWDRequest_Parity(0, 1, 0, 0);

	TEST_ASSERT_EQUAL(1,Parity);
}

void test_check_SWDRequest_Parity_should_return_1_if_input_1011()
{
	int Parity = 0 ;
	Parity = check_SWDRequest_Parity(1, 0, 1, 1);

	TEST_ASSERT_EQUAL(1,Parity);
}


void test_check_SWDRequest_Parity_should_return_1_0110()
{
	int Parity = 0 ;
	Parity = check_SWDRequest_Parity(0, 1, 1, 0);

	TEST_ASSERT_EQUAL(0,Parity);
}

void test_check_SWDRequest_Parity_should_return_1_1111()
{
	int Parity = 0 ;
	Parity = check_SWDRequest_Parity(1, 1, 1, 1);

	TEST_ASSERT_EQUAL(0,Parity);
}

void test_checkAddressbit_0x08_bit3_should_return_1()
{
	TEST_ASSERT_EQUAL(1,checkAddressbit(0x08,3));
}

void test_checkAddressbit_0x08_bit2_should_return_0()
{
	TEST_ASSERT_EQUAL(0,checkAddressbit(0x08,2));
}

void test_checkAddressbit_0x40_bit2_should_return_0()
{
	TEST_ASSERT_EQUAL(1,checkAddressbit(0x40,6));
}

void test_SWD_Request_given_Address0x00_DP_Read_should_return_0xA5()
{
	int request = 0 ;

	//DP = 0 , AP = 1
	//WRiTE = 0 ,READ = 1

	//**Note LSB
	//Start bit	|	APnDP	|	RW	|	Addr2	|	Addr3	|	Parity	|	Stop	|	Park	|
	//    1     |	0		|	1	| 	0		|	0		|	1		|	0		|	1		|

	request = SWD_Request(DP,READ,0x00);

	TEST_ASSERT_EQUAL(0xA5,request);
}

void test_SWD_Request_given_Address0x08_AP_Write_should_return_0x93()
{
	int request = 0 ;

	//DP = 0 , AP = 1
	//WRiTE = 0 ,READ = 1

	//**Note LSB
	//Start bit	|	APnDP	|	RW	|	Addr2	|	Addr3	|	Parity	|	Stop	|	Park	|
	//    1     |	1		|	0	| 	0		|	1		|	0		|	0		|	1		|

	request = SWD_Request(AP,WRITE,0x08);

	TEST_ASSERT_EQUAL(0x93,request);
}

void test_sendSWDRequest_0xA5_should_send0xA5_call_turnAround_SWDIO_InputMode()
{
	//0xA5 = 1010 0101

	// 0x5
	//send 1
	SWCLK_OFF_Expect();SWDIO_High_Expect();SWCLK_ON_Expect();
	//send 0
	SWCLK_OFF_Expect();SWDIO_Low_Expect();SWCLK_ON_Expect();
	//send 1
	SWCLK_OFF_Expect();SWDIO_High_Expect();SWCLK_ON_Expect();
	//send 0
	SWCLK_OFF_Expect();SWDIO_Low_Expect();SWCLK_ON_Expect();

	//0xA
	//send 0
	SWCLK_OFF_Expect();SWDIO_Low_Expect();SWCLK_ON_Expect();
	//send 1
	SWCLK_OFF_Expect();SWDIO_High_Expect();SWCLK_ON_Expect();
	//send 0
	SWCLK_OFF_Expect();SWDIO_Low_Expect();SWCLK_ON_Expect();
	//send 1
	SWCLK_OFF_Expect();SWDIO_High_Expect();SWCLK_ON_Expect();

	turnAround_Expect();
	SWDIO_InputMode_Expect();
	sendSWDRequest(0xA5);
}

void test_sendSWDRequest_0xC3_should_send0xC3_call_turnAround_SWDIO_InputMode()
{
	//0xC3 = 1100 0011

	// 0x3
	//send 1
	SWCLK_OFF_Expect();SWDIO_High_Expect();SWCLK_ON_Expect();
	//send 1
	SWCLK_OFF_Expect();SWDIO_High_Expect();SWCLK_ON_Expect();
	//send 0
	SWCLK_OFF_Expect();SWDIO_Low_Expect();SWCLK_ON_Expect();
	//send 0
	SWCLK_OFF_Expect();SWDIO_Low_Expect();SWCLK_ON_Expect();

	//0xC
	//send 0
	SWCLK_OFF_Expect();SWDIO_Low_Expect();SWCLK_ON_Expect();
	//send 0
	SWCLK_OFF_Expect();SWDIO_Low_Expect();SWCLK_ON_Expect();
	//send 1
	SWCLK_OFF_Expect();SWDIO_High_Expect();SWCLK_ON_Expect();
	//send 1
	SWCLK_OFF_Expect();SWDIO_High_Expect();SWCLK_ON_Expect();


	turnAround_Expect();
	SWDIO_InputMode_Expect();
	sendSWDRequest(0xC3);
}

//Mocking ACK = OK = 0x1
//Mocking IDCODE = 0x2ba01477
//Parity = 0
void test_initialisation_should_call_SWDIO_LowHigh_switchJTAGtoSWD_sendSWDRequest0xA5_readACK_readIDCODE_readParity_extraIdleCLock_lineReset()
{
	SWDIO_LowHigh_Expect();

	//switchJTAGtoSWDlineReset_Expect();
	lineReset_Expect();

	SWCLK_OFF_Expect();SWDIO_Low_Expect();SWCLK_ON_Expect();
	SWCLK_OFF_Expect();SWDIO_High_Expect();SWCLK_ON_Expect();
	SWCLK_OFF_Expect();SWDIO_High_Expect();SWCLK_ON_Expect();
	SWCLK_OFF_Expect();SWDIO_High_Expect();SWCLK_ON_Expect();

	SWCLK_OFF_Expect();SWDIO_High_Expect();SWCLK_ON_Expect();
	SWCLK_OFF_Expect();SWDIO_Low_Expect();SWCLK_ON_Expect();
	SWCLK_OFF_Expect();SWDIO_Low_Expect();SWCLK_ON_Expect();
	SWCLK_OFF_Expect();SWDIO_High_Expect();SWCLK_ON_Expect();

	SWCLK_OFF_Expect();SWDIO_High_Expect();SWCLK_ON_Expect();
	SWCLK_OFF_Expect();SWDIO_High_Expect();SWCLK_ON_Expect();
	SWCLK_OFF_Expect();SWDIO_High_Expect();SWCLK_ON_Expect();
	SWCLK_OFF_Expect();SWDIO_Low_Expect();SWCLK_ON_Expect();

	SWCLK_OFF_Expect();SWDIO_Low_Expect();SWCLK_ON_Expect();
	SWCLK_OFF_Expect();SWDIO_High_Expect();SWCLK_ON_Expect();
	SWCLK_OFF_Expect();SWDIO_High_Expect();SWCLK_ON_Expect();
	SWCLK_OFF_Expect();SWDIO_High_Expect();SWCLK_ON_Expect();

	lineReset_Expect();

	extraIdleClock_Expect(3);

	//sendSWDRequest 0xA5
	SWCLK_OFF_Expect();SWDIO_High_Expect();SWCLK_ON_Expect();
	SWCLK_OFF_Expect();SWDIO_Low_Expect();SWCLK_ON_Expect();
	SWCLK_OFF_Expect();SWDIO_High_Expect();SWCLK_ON_Expect();
	SWCLK_OFF_Expect();SWDIO_Low_Expect();SWCLK_ON_Expect();

	SWCLK_OFF_Expect();SWDIO_Low_Expect();SWCLK_ON_Expect();
	SWCLK_OFF_Expect();SWDIO_High_Expect();SWCLK_ON_Expect();
	SWCLK_OFF_Expect();SWDIO_Low_Expect();SWCLK_ON_Expect();
	SWCLK_OFF_Expect();SWDIO_High_Expect();SWCLK_ON_Expect();

	turnAround_Expect();
	SWDIO_InputMode_Expect();

	//read ACK = OK = 0x1 = 0001
	SWCLK_ON_Expect();SWCLK_OFF_Expect();readSWDIO_Pin_ExpectAndReturn(1); // LSB
	SWCLK_ON_Expect();SWCLK_OFF_Expect();readSWDIO_Pin_ExpectAndReturn(0);
	SWCLK_ON_Expect();SWCLK_OFF_Expect();readSWDIO_Pin_ExpectAndReturn(0);

	//read IDCODE = 0x2ba01477 = 0010 1011 1010 0000 0001 0100 0111 0111
	SWCLK_ON_Expect();SWCLK_OFF_Expect();readSWDIO_Pin_ExpectAndReturn(1); // LSB
	SWCLK_ON_Expect();SWCLK_OFF_Expect();readSWDIO_Pin_ExpectAndReturn(1);
	SWCLK_ON_Expect();SWCLK_OFF_Expect();readSWDIO_Pin_ExpectAndReturn(1); // 7
	SWCLK_ON_Expect();SWCLK_OFF_Expect();readSWDIO_Pin_ExpectAndReturn(0);

	SWCLK_ON_Expect();SWCLK_OFF_Expect();readSWDIO_Pin_ExpectAndReturn(1);
	SWCLK_ON_Expect();SWCLK_OFF_Expect();readSWDIO_Pin_ExpectAndReturn(1);
	SWCLK_ON_Expect();SWCLK_OFF_Expect();readSWDIO_Pin_ExpectAndReturn(1); // 7
	SWCLK_ON_Expect();SWCLK_OFF_Expect();readSWDIO_Pin_ExpectAndReturn(0);

	SWCLK_ON_Expect();SWCLK_OFF_Expect();readSWDIO_Pin_ExpectAndReturn(1);
	SWCLK_ON_Expect();SWCLK_OFF_Expect();readSWDIO_Pin_ExpectAndReturn(0);
	SWCLK_ON_Expect();SWCLK_OFF_Expect();readSWDIO_Pin_ExpectAndReturn(0); // 4
	SWCLK_ON_Expect();SWCLK_OFF_Expect();readSWDIO_Pin_ExpectAndReturn(0);

	SWCLK_ON_Expect();SWCLK_OFF_Expect();readSWDIO_Pin_ExpectAndReturn(0);
	SWCLK_ON_Expect();SWCLK_OFF_Expect();readSWDIO_Pin_ExpectAndReturn(0); // 1
	SWCLK_ON_Expect();SWCLK_OFF_Expect();readSWDIO_Pin_ExpectAndReturn(1);
	SWCLK_ON_Expect();SWCLK_OFF_Expect();readSWDIO_Pin_ExpectAndReturn(0);

	SWCLK_ON_Expect();SWCLK_OFF_Expect();readSWDIO_Pin_ExpectAndReturn(0);
	SWCLK_ON_Expect();SWCLK_OFF_Expect();readSWDIO_Pin_ExpectAndReturn(0); // 0
	SWCLK_ON_Expect();SWCLK_OFF_Expect();readSWDIO_Pin_ExpectAndReturn(0);
	SWCLK_ON_Expect();SWCLK_OFF_Expect();readSWDIO_Pin_ExpectAndReturn(0);

	SWCLK_ON_Expect();SWCLK_OFF_Expect();readSWDIO_Pin_ExpectAndReturn(0);
	SWCLK_ON_Expect();SWCLK_OFF_Expect();readSWDIO_Pin_ExpectAndReturn(1);
	SWCLK_ON_Expect();SWCLK_OFF_Expect();readSWDIO_Pin_ExpectAndReturn(0); // a
	SWCLK_ON_Expect();SWCLK_OFF_Expect();readSWDIO_Pin_ExpectAndReturn(1);

	SWCLK_ON_Expect();SWCLK_OFF_Expect();readSWDIO_Pin_ExpectAndReturn(1);
	SWCLK_ON_Expect();SWCLK_OFF_Expect();readSWDIO_Pin_ExpectAndReturn(1); // b
	SWCLK_ON_Expect();SWCLK_OFF_Expect();readSWDIO_Pin_ExpectAndReturn(0);
	SWCLK_ON_Expect();SWCLK_OFF_Expect();readSWDIO_Pin_ExpectAndReturn(1);

	SWCLK_ON_Expect();SWCLK_OFF_Expect();readSWDIO_Pin_ExpectAndReturn(0);
	SWCLK_ON_Expect();SWCLK_OFF_Expect();readSWDIO_Pin_ExpectAndReturn(1); // 2
	SWCLK_ON_Expect();SWCLK_OFF_Expect();readSWDIO_Pin_ExpectAndReturn(0);
	SWCLK_ON_Expect();SWCLK_OFF_Expect();readSWDIO_Pin_ExpectAndReturn(0);

	//read Parity = 0
	SWCLK_ON_Expect();SWCLK_OFF_Expect();readSWDIO_Pin_ExpectAndReturn(0);


	//8 extraIdleClock
	extraIdleClock_Expect(8);

	//lineReset
	lineReset_Expect();

	initialisation();
}
