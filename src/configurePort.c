#include "configurePort.h"

GPIO_InitTypeDef GpioInfo;

void configureClock()   {
	__GPIOB_CLK_ENABLE();

	GpioInfo.Mode = GPIO_MODE_OUTPUT_PP ;
	GpioInfo.Pin = GPIO_PIN_10 ; // PB10 as clock output
	GpioInfo.Pull = GPIO_NOPULL ;
	GpioInfo.Speed = GPIO_SPEED_FAST ;

	HAL_GPIO_Init(GPIOB,&GpioInfo);
}

void configureTargetResetPin()  {
	GpioInfo.Mode = GPIO_MODE_OUTPUT_OD ;
	GpioInfo.Pin = GPIO_PIN_13; // PB13 as target reset pin
	GpioInfo.Pull = GPIO_PULLUP ;
	GpioInfo.Speed = GPIO_SPEED_FAST ;

	HAL_GPIO_Init(GPIOB,&GpioInfo);
}


void SWDIO_OutputMode() {
	GpioInfo.Mode = GPIO_MODE_OUTPUT_PP;
	GpioInfo.Pin = GPIO_PIN_12; // PB12 as output
	GpioInfo.Pull = GPIO_PULLUP ;
	GpioInfo.Speed = GPIO_SPEED_FAST ;

	HAL_GPIO_Init(GPIOB,&GpioInfo);
}

void SWDIO_InputMode()  {
	GpioInfo.Mode = GPIO_MODE_INPUT ;
	GpioInfo.Pin = GPIO_PIN_12; // PB12 as input
	GpioInfo.Pull = GPIO_PULLUP;
	GpioInfo.Speed = GPIO_SPEED_FAST ;

	HAL_GPIO_Init(GPIOB,&GpioInfo);
}


void config_ClkAndIO()
{
	configureClock();
	configureTargetResetPin();
    SWDIO_OutputMode();
}
