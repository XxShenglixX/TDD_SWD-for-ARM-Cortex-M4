#include "unity.h"
#include <stdint.h>
#include "Reset.h"
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

void test_lineReset_should_call_generate_53clockcycles_with_SWDIO_High()
{
	int i = 0 ;
	SWDIO_High_Expect();
	for ( i = 0 ; i < 53; i ++)
		clockGenerator_1cycle_Expect();
	lineReset();
}

void test_resetTarget_should_call_ResetPinLow_ResetPin_High()
{
	ResetPin_Low_Expect();
	delay_Expect(500,1,1);
	ResetPin_High_Expect();
	delay_Expect(2600,1,1);

	resetTarget();
}