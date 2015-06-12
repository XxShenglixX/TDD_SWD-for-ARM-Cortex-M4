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

/*void test_lineReset_should_call_generate_53clockcycles_with_SWDIO_High()
{
	
	lineReset();
}*/