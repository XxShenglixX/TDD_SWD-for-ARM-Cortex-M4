#include "unity.h"
#include "Bit_ReadSend.h"
#include "mock_configurePort.h"
#include "mock_IO_Operations.h"
#include "mock_Delay.h"
#include "Reset.h"
#include "swdProtocol.h"
#include <stdint.h>

void setUp(void)
{
}

void tearDown(void)
{
}

void test_sendBit_SWDIO_should_HIGH_after_1_bit_is_sent()
{
	int singleBit = 1;

	//clock at falling edge
	SWCLK_OFF_Expect();

	//received 1 bit SWDIO set HIGH
	SWDIO_High_Expect();

	//clock goes high
	SWCLK_ON_Expect();

	//call function here
	sendBit(singleBit);
}

void test_sendBit_SWDIO_should_LOW_after_0_bit_is_sent()
{
	int singleBit = 0;

	//clock at falling edge
	SWCLK_OFF_Expect();

	//received 0 bit SWDIO set LOW
	SWDIO_Low_Expect();

	//clock goes high
	SWCLK_ON_Expect();

	//call function here
	sendBit(singleBit);
}

void test_sendBits_send_hex_0x02_SWDIO_should_show_0_then_1()
{
	int dataToSend = 0x02;

	//clock low
	SWCLK_OFF_Expect();

	// 0
	SWDIO_Low_Expect();

	//clock high
	SWCLK_ON_Expect();

	//clock low
	SWCLK_OFF_Expect();

	// 1
	SWDIO_High_Expect();

	//clock high
	SWCLK_ON_Expect();

	//call function here
	sendBits(dataToSend, 2);
}

void test_sendBits_send_hex_0x14_SWDIO_should_set_00101()
{
	int dataToSend = 0x14;

	SWCLK_OFF_Expect();

	// 0
	SWDIO_Low_Expect();

	SWCLK_ON_Expect();

	SWCLK_OFF_Expect();

	// 0
	SWDIO_Low_Expect();

	SWCLK_ON_Expect();

	SWCLK_OFF_Expect();

	// 1
	SWDIO_High_Expect();

	SWCLK_ON_Expect();

	SWCLK_OFF_Expect();

	// 0
	SWDIO_Low_Expect();

	SWCLK_ON_Expect();

	SWCLK_OFF_Expect();

	// 1
	SWDIO_High_Expect();

	SWCLK_ON_Expect();

	//call function here
	sendBits(dataToSend, 5);
}

void test_sendBits_send_hex_0XE79E_SWDIO_should_set_0111_1001_1110_0111()
{
	int dataToSend = 0XE79E;

	SWCLK_OFF_Expect();
	// 0
	SWDIO_Low_Expect();
	SWCLK_ON_Expect();

	SWCLK_OFF_Expect();
	// 1
	SWDIO_High_Expect();
	SWCLK_ON_Expect();

	SWCLK_OFF_Expect();
	// 1
	SWDIO_High_Expect();
	SWCLK_ON_Expect();

	SWCLK_OFF_Expect();
	// 1
	SWDIO_High_Expect();
	SWCLK_ON_Expect();
  //----------------

	SWCLK_OFF_Expect();
	// 1
	SWDIO_High_Expect();
	SWCLK_ON_Expect();

  SWCLK_OFF_Expect();
	// 0
	SWDIO_Low_Expect();
	SWCLK_ON_Expect();

	SWCLK_OFF_Expect();
	// 0
	SWDIO_Low_Expect();
	SWCLK_ON_Expect();

	SWCLK_OFF_Expect();
	// 1
	SWDIO_High_Expect();
	SWCLK_ON_Expect();
  //----------------

	SWCLK_OFF_Expect();
	// 1
	SWDIO_High_Expect();
	SWCLK_ON_Expect();

	SWCLK_OFF_Expect();
	// 1
	SWDIO_High_Expect();
	SWCLK_ON_Expect();

  SWCLK_OFF_Expect();
	// 1
	SWDIO_High_Expect();
	SWCLK_ON_Expect();

	SWCLK_OFF_Expect();
	// 0
	SWDIO_Low_Expect();
	SWCLK_ON_Expect();
  //----------------

	SWCLK_OFF_Expect();
	// 0
	SWDIO_Low_Expect();
	SWCLK_ON_Expect();

	SWCLK_OFF_Expect();
	// 1
	SWDIO_High_Expect();
	SWCLK_ON_Expect();

	SWCLK_OFF_Expect();
	// 1
	SWDIO_High_Expect();
	SWCLK_ON_Expect();

  SWCLK_OFF_Expect();
	// 1
	SWDIO_High_Expect();
	SWCLK_ON_Expect();
  //----------------

	//call function here
	sendBits(dataToSend, 16);
}

void test_readBit_dataToRead_is_bit_1_should_read_1()
{
  int dataToRead = 0;
  
  SWCLK_ON_Expect();
	SWCLK_OFF_Expect();
  readSWDIO_Pin_ExpectAndReturn(1);
  
  TEST_ASSERT_EQUAL(readBit(), 1);
}

void test_readBit_dataToRead_is_bit_0_should_read_0()
{
  int dataToRead = 0;
  
  SWCLK_ON_Expect();
	SWCLK_OFF_Expect();
  readSWDIO_Pin_ExpectAndReturn(0);
  
  TEST_ASSERT_EQUAL(readBit(), 0);
}

void test_readBits_dataToRead_is_0x04_should_read_001()
{
  int dataToRead = 0;
  
  SWCLK_ON_Expect();
	SWCLK_OFF_Expect();
  readSWDIO_Pin_ExpectAndReturn(1);
  
  SWCLK_ON_Expect();
	SWCLK_OFF_Expect();
  readSWDIO_Pin_ExpectAndReturn(0);
  
  SWCLK_ON_Expect();
	SWCLK_OFF_Expect();
  readSWDIO_Pin_ExpectAndReturn(0);

  readBits((uint32_t *)&dataToRead, 3);
  
  TEST_ASSERT_EQUAL(dataToRead, 1);
}

void test_readBits_dataToRead_is_0xEE_should_read_01110111()
{
  int dataToRead = 0;
  
  SWCLK_ON_Expect();
	SWCLK_OFF_Expect();
  readSWDIO_Pin_ExpectAndReturn(1);
  
  SWCLK_ON_Expect();
	SWCLK_OFF_Expect();
  readSWDIO_Pin_ExpectAndReturn(1);
  
  SWCLK_ON_Expect();
	SWCLK_OFF_Expect();
  readSWDIO_Pin_ExpectAndReturn(1);
  
  SWCLK_ON_Expect();
	SWCLK_OFF_Expect();
  readSWDIO_Pin_ExpectAndReturn(0);
  
  SWCLK_ON_Expect();
	SWCLK_OFF_Expect();
  readSWDIO_Pin_ExpectAndReturn(1);
  
  SWCLK_ON_Expect();
	SWCLK_OFF_Expect();
  readSWDIO_Pin_ExpectAndReturn(1);
  
  SWCLK_ON_Expect();
	SWCLK_OFF_Expect();
  readSWDIO_Pin_ExpectAndReturn(1);
  
  SWCLK_ON_Expect();
	SWCLK_OFF_Expect();
  readSWDIO_Pin_ExpectAndReturn(0);
  

  readBits((uint32_t *)&dataToRead, 8);
  
  TEST_ASSERT_EQUAL(dataToRead, 0x77);
}


