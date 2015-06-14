#ifndef ClkAndIO_Control_H
#define ClkAndIO_Control_H

void SWCLK_ON();
void SWCLK_OFF();
void SWDIO_High();
void SWDIO_Low();

void ResetPin_High();
void ResetPin_Low();

void clockGenerator_1cycle();
void extraIdleClock(int numberOfClocks);
int readSWDIO_Pin();

void turnAround();
void SWDIO_LowHigh();

#endif // ClkAndIO_Control_H