/*
 * scheduler_OS.c
 *
 * Created: 09/05/2024 01:35:51 م
 *  Author: Azza Saeed
 */ 

#define F_CPU 8000000UL
#include <util/delay.h>

#include "Scheduler_interface.h"
#include "dio.h"

void Init_vidTask(void);
void Red_vidled(void);
void Green_vidLed(void);

int main(void)
{
	Init_vidTask();
	
	Create_u8task(1,1,0,Red_vidled);
	Create_u8task(2,2,1,Green_vidLed);
	
	Start_voidSchaduler();
    while(1)
    {
        //TODO:: Please write your application code 
    }
}
void Init_vidTask(void)
{
	dio_vidConfigChannel(DIO_PORTA,1,OUTPUT);
	dio_vidConfigChannel(DIO_PORTA,2,OUTPUT);
}
void Red_vidled(void)
{
	dio_vidFlipChannel(DIO_PORTA,1);
	_delay_ms(100);
}
void Green_vidLed(void)
{
	dio_vidFlipChannel(DIO_PORTA,2);
	_delay_ms(200);
}