#include "configurePort.h"

void configureClock()
{
	GPIO_InitTypeDef GpioInfo;
	__GPIOB_CLK_ENABLE();

	GpioInfo.Mode = GPIO_MODE_OUTPUT_PP ;
	GpioInfo.Pin = GPIO_PIN_10 ; // PB10 as clock output
	GpioInfo.Pull = GPIO_NOPULL ;
	GpioInfo.Speed = GPIO_SPEED_FAST ;

	HAL_GPIO_Init(GPIOB,&GpioInfo);
}

void configureTargetResetPin()
{
	GPIO_InitTypeDef GpioInfo;

	GpioInfo.Mode = GPIO_MODE_OUTPUT_OD ;
	GpioInfo.Pin = GPIO_PIN_13; // PB13 as target reset pin
	GpioInfo.Pull = GPIO_PULLUP ;
	GpioInfo.Speed = GPIO_SPEED_FAST ;

	HAL_GPIO_Init(GPIOB,&GpioInfo);
}


void SWDIO_OutputMode()
{
	GPIO_InitTypeDef GpioInfo;

	GpioInfo.Mode = GPIO_MODE_OUTPUT_PP;
	GpioInfo.Pin = GPIO_PIN_12; // PB12 as output
	GpioInfo.Pull = GPIO_PULLUP ;
	GpioInfo.Speed = GPIO_SPEED_FAST ;

	HAL_GPIO_Init(GPIOB,&GpioInfo);
}

void SWDIO_InputMode()
{
	GPIO_InitTypeDef GpioInfo;

	GpioInfo.Mode = GPIO_MODE_INPUT ;
	GpioInfo.Pin = GPIO_PIN_12; // PB12 as input
	GpioInfo.Pull = GPIO_PULLUP;
	GpioInfo.Speed = GPIO_SPEED_FAST ;

	HAL_GPIO_Init(GPIOB,&GpioInfo);
}


void configure_IOPorts()
{
	configureClock();
	configureTargetResetPin();
	SWDIO_OutputMode();
}
