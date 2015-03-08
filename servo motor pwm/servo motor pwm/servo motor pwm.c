/*
 * servo_motor_pwm.c
 *
 * Created: 2/27/2015 6:18:50 PM
 *  Author: Anurag
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
int main(void)
{   TCCR1A|=1<<COM1A1|1<<COM1A0|1<<WGM11;
	TCCR1B|=1<<WGM12|1<<WGM13|1<<CS10|1<<CS11;
	ICR1=4999;
	DDRD=0xff;
    while(1)
    {
       OCR1A=ICR1-375;
	   _delay_ms(1000);
	    OCR1A=ICR1-600;
	    _delay_ms(1000);
		 OCR1A=ICR1-137.5;
		 _delay_ms(1000);
    }
}