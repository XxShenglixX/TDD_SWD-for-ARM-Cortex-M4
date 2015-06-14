#include "unity.h"
#include "Reset.h"
#include <stdint.h>
#include "Bit_ReadSend.h"
#include "swdProtocol.h"
#include "mock_configurePort.h"
#include "mock_ClkAndIO_Control.h"
#include "mock_Delay.h"

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

	// 1
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

	// 0
	SWDIO_Low_Expect();

	//clock goes high
	SWCLK_ON_Expect();

	//call function here
	sendBit(singleBit);
}

void test_sendBits_send_hex_0x02_SWDIO_should_show_0_then_1()
{
	int dataToSend = 0x02;

	SWCLK_OFF_Expect();SWDIO_Low_Expect();SWCLK_ON_Expect();    // 0
	SWCLK_OFF_Expect();SWDIO_High_Expect();SWCLK_ON_Expect();   // 1

	//call function here
	sendBits(dataToSend, 2);
}

void test_sendBits_send_hex_0x14_SWDIO_should_set_00101()
{
	int dataToSend = 0x14;

    SWCLK_OFF_Expect();SWDIO_Low_Expect();SWCLK_ON_Expect();    // 0
    SWCLK_OFF_Expect();SWDIO_Low_Expect();SWCLK_ON_Expect();    // 0
    SWCLK_OFF_Expect();SWDIO_High_Expect();SWCLK_ON_Expect();   // 1
    SWCLK_OFF_Expect();SWDIO_Low_Expect();SWCLK_ON_Expect();    // 0
    SWCLK_OFF_Expect();SWDIO_High_Expect();SWCLK_ON_Expect();   // 1

	//call function here
	sendBits(dataToSend, 5);
}

void test_sendBits_send_hex_0XE79E_SWDIO_should_set_0111_1001_1110_0111()
{
	int dataToSend = 0XE79E;

    SWCLK_OFF_Expect();SWDIO_Low_Expect();SWCLK_ON_Expect();    // 0
    SWCLK_OFF_Expect();SWDIO_High_Expect();SWCLK_ON_Expect();   // 1
    SWCLK_OFF_Expect();SWDIO_High_Expect();SWCLK_ON_Expect();   // 1
    SWCLK_OFF_Expect();SWDIO_High_Expect();SWCLK_ON_Expect();   // 1

    SWCLK_OFF_Expect();SWDIO_High_Expect();SWCLK_ON_Expect();   // 1
    SWCLK_OFF_Expect();SWDIO_Low_Expect();SWCLK_ON_Expect();    // 0
    SWCLK_OFF_Expect();SWDIO_Low_Expect();SWCLK_ON_Expect();    // 0
    SWCLK_OFF_Expect();SWDIO_High_Expect();SWCLK_ON_Expect();   // 1

    SWCLK_OFF_Expect();SWDIO_High_Expect();SWCLK_ON_Expect();   // 1
    SWCLK_OFF_Expect();SWDIO_High_Expect();SWCLK_ON_Expect();   // 1
    SWCLK_OFF_Expect();SWDIO_High_Expect();SWCLK_ON_Expect();   // 1
    SWCLK_OFF_Expect();SWDIO_Low_Expect();SWCLK_ON_Expect();    // 0

    SWCLK_OFF_Expect();SWDIO_Low_Expect();SWCLK_ON_Expect();    // 0
    SWCLK_OFF_Expect();SWDIO_High_Expect();SWCLK_ON_Expect();   // 1
    SWCLK_OFF_Expect();SWDIO_High_Expect();SWCLK_ON_Expect();   // 1
    SWCLK_OFF_Expect();SWDIO_High_Expect();SWCLK_ON_Expect();   // 1

	//call function here
	sendBits(dataToSend, 16);
}

void test_sendBits_send_hex_0x5FA68D20_SWDIO_should_set_0000_0100_1011_0001_0110_0101_1111_1010()
{
	uint32_t dataToSend = 0x5FA68D20;

    SWCLK_OFF_Expect();SWDIO_Low_Expect();SWCLK_ON_Expect();    // 0
    SWCLK_OFF_Expect();SWDIO_Low_Expect();SWCLK_ON_Expect();    // 0
    SWCLK_OFF_Expect();SWDIO_Low_Expect();SWCLK_ON_Expect();    // 0
    SWCLK_OFF_Expect();SWDIO_Low_Expect();SWCLK_ON_Expect();    // 0

    SWCLK_OFF_Expect();SWDIO_Low_Expect();SWCLK_ON_Expect();    // 0
    SWCLK_OFF_Expect();SWDIO_High_Expect();SWCLK_ON_Expect();    // 1
    SWCLK_OFF_Expect();SWDIO_Low_Expect();SWCLK_ON_Expect();    // 0
    SWCLK_OFF_Expect();SWDIO_Low_Expect();SWCLK_ON_Expect();    // 0

    SWCLK_OFF_Expect();SWDIO_High_Expect();SWCLK_ON_Expect();   // 1
    SWCLK_OFF_Expect();SWDIO_Low_Expect();SWCLK_ON_Expect();    // 0
    SWCLK_OFF_Expect();SWDIO_High_Expect();SWCLK_ON_Expect();   // 1
    SWCLK_OFF_Expect();SWDIO_High_Expect();SWCLK_ON_Expect();   // 1

    SWCLK_OFF_Expect();SWDIO_Low_Expect();SWCLK_ON_Expect();    // 0
    SWCLK_OFF_Expect();SWDIO_Low_Expect();SWCLK_ON_Expect();    // 0
    SWCLK_OFF_Expect();SWDIO_Low_Expect();SWCLK_ON_Expect();    // 0
    SWCLK_OFF_Expect();SWDIO_High_Expect();SWCLK_ON_Expect();   // 1

    SWCLK_OFF_Expect();SWDIO_Low_Expect();SWCLK_ON_Expect();    // 0
    SWCLK_OFF_Expect();SWDIO_High_Expect();SWCLK_ON_Expect();   // 1
    SWCLK_OFF_Expect();SWDIO_High_Expect();SWCLK_ON_Expect();   // 1
    SWCLK_OFF_Expect();SWDIO_Low_Expect();SWCLK_ON_Expect();    // 0

    SWCLK_OFF_Expect();SWDIO_Low_Expect();SWCLK_ON_Expect();    // 0
    SWCLK_OFF_Expect();SWDIO_High_Expect();SWCLK_ON_Expect();   // 1
    SWCLK_OFF_Expect();SWDIO_Low_Expect();SWCLK_ON_Expect();    // 0
    SWCLK_OFF_Expect();SWDIO_High_Expect();SWCLK_ON_Expect();   // 1

    SWCLK_OFF_Expect();SWDIO_High_Expect();SWCLK_ON_Expect();   // 1
    SWCLK_OFF_Expect();SWDIO_High_Expect();SWCLK_ON_Expect();   // 1
    SWCLK_OFF_Expect();SWDIO_High_Expect();SWCLK_ON_Expect();   // 1
    SWCLK_OFF_Expect();SWDIO_High_Expect();SWCLK_ON_Expect();   // 1

    SWCLK_OFF_Expect();SWDIO_High_Expect();SWCLK_ON_Expect();   // 1
    SWCLK_OFF_Expect();SWDIO_Low_Expect();SWCLK_ON_Expect();    // 0
    SWCLK_OFF_Expect();SWDIO_High_Expect();SWCLK_ON_Expect();   // 1
    SWCLK_OFF_Expect();SWDIO_Low_Expect();SWCLK_ON_Expect();    // 0

	//call function here
	sendBits(dataToSend, 32);
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

void test_readBits_dataToRead_is_0x04_should_read_1()
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

void test_readBits_dataToRead_hex_0xEE2805D4_SWDIO_should_read_0x2ba01477()
{
	uint32_t dataToRead = 0;

	SWCLK_ON_Expect();SWCLK_OFF_Expect();readSWDIO_Pin_ExpectAndReturn(1); // LSB
	SWCLK_ON_Expect();SWCLK_OFF_Expect();readSWDIO_Pin_ExpectAndReturn(1);
	SWCLK_ON_Expect();SWCLK_OFF_Expect();readSWDIO_Pin_ExpectAndReturn(1); // E
	SWCLK_ON_Expect();SWCLK_OFF_Expect();readSWDIO_Pin_ExpectAndReturn(0);

	SWCLK_ON_Expect();SWCLK_OFF_Expect();readSWDIO_Pin_ExpectAndReturn(1);
	SWCLK_ON_Expect();SWCLK_OFF_Expect();readSWDIO_Pin_ExpectAndReturn(1);
	SWCLK_ON_Expect();SWCLK_OFF_Expect();readSWDIO_Pin_ExpectAndReturn(1); // E
	SWCLK_ON_Expect();SWCLK_OFF_Expect();readSWDIO_Pin_ExpectAndReturn(0);

	SWCLK_ON_Expect();SWCLK_OFF_Expect();readSWDIO_Pin_ExpectAndReturn(0);
	SWCLK_ON_Expect();SWCLK_OFF_Expect();readSWDIO_Pin_ExpectAndReturn(0);
	SWCLK_ON_Expect();SWCLK_OFF_Expect();readSWDIO_Pin_ExpectAndReturn(1); // 2
	SWCLK_ON_Expect();SWCLK_OFF_Expect();readSWDIO_Pin_ExpectAndReturn(0);

	SWCLK_ON_Expect();SWCLK_OFF_Expect();readSWDIO_Pin_ExpectAndReturn(1);
	SWCLK_ON_Expect();SWCLK_OFF_Expect();readSWDIO_Pin_ExpectAndReturn(0); // 8
	SWCLK_ON_Expect();SWCLK_OFF_Expect();readSWDIO_Pin_ExpectAndReturn(0);
	SWCLK_ON_Expect();SWCLK_OFF_Expect();readSWDIO_Pin_ExpectAndReturn(0);

	SWCLK_ON_Expect();SWCLK_OFF_Expect();readSWDIO_Pin_ExpectAndReturn(0);
	SWCLK_ON_Expect();SWCLK_OFF_Expect();readSWDIO_Pin_ExpectAndReturn(0); // 0
	SWCLK_ON_Expect();SWCLK_OFF_Expect();readSWDIO_Pin_ExpectAndReturn(0);
	SWCLK_ON_Expect();SWCLK_OFF_Expect();readSWDIO_Pin_ExpectAndReturn(0);

	SWCLK_ON_Expect();SWCLK_OFF_Expect();readSWDIO_Pin_ExpectAndReturn(0);
	SWCLK_ON_Expect();SWCLK_OFF_Expect();readSWDIO_Pin_ExpectAndReturn(1);
	SWCLK_ON_Expect();SWCLK_OFF_Expect();readSWDIO_Pin_ExpectAndReturn(0); // 5
	SWCLK_ON_Expect();SWCLK_OFF_Expect();readSWDIO_Pin_ExpectAndReturn(1);

	SWCLK_ON_Expect();SWCLK_OFF_Expect();readSWDIO_Pin_ExpectAndReturn(1);
	SWCLK_ON_Expect();SWCLK_OFF_Expect();readSWDIO_Pin_ExpectAndReturn(1); // D
	SWCLK_ON_Expect();SWCLK_OFF_Expect();readSWDIO_Pin_ExpectAndReturn(0);
	SWCLK_ON_Expect();SWCLK_OFF_Expect();readSWDIO_Pin_ExpectAndReturn(1);

	SWCLK_ON_Expect();SWCLK_OFF_Expect();readSWDIO_Pin_ExpectAndReturn(0);
	SWCLK_ON_Expect();SWCLK_OFF_Expect();readSWDIO_Pin_ExpectAndReturn(1); // 4
	SWCLK_ON_Expect();SWCLK_OFF_Expect();readSWDIO_Pin_ExpectAndReturn(0);
	SWCLK_ON_Expect();SWCLK_OFF_Expect();readSWDIO_Pin_ExpectAndReturn(0);


    readBits(&dataToRead, 32);

    TEST_ASSERT_EQUAL(dataToRead, 0x2ba01477);
}


