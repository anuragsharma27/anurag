/*
 * i2c1.c
 *
 * Created: 3/3/2015 7:30:53 AM
 *  Author: Anurag
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

void TWI_init_master(void)
{
	TWBR=0x01;                // Bit rate
    TWSR|=(0<<TWPS1|0<<TWPS0);   // Setting prescalar bits
                                 // SCL freq= F_CPU/(16+2(TWBR).4^TWPS)
}

void master_start()
{
	TWCR|=1<<TWINT|1<<TWSTA|1<<TWEN;
	while (!(TWCR & 1<<TWINT));
	while((TWSR & 0xF8)!=0x08);   // Check for  acknowledgement
	
}
void TWI_read_address(unsigned char data)
{
	TWDR=data;    // Address and read instruction
	TWCR=(1<<TWINT)|(1<<TWEN);    // Clear TWI interrupt flag,Enable TWI
	while (!(TWCR & (1<<TWINT))); // Wait till complete TWDR byte received
	//PORTB=0xff;
	while((TWSR & 0xF8)!= 0x18);  // Check for the acknoledgement
	//PORTB=0xff;
}
void TWI_write_data(unsigned char data)
{
	TWDR=data;    // put data in TWDR
	TWCR=(1<<TWINT)|(1<<TWEN);    // Clear TWI interrupt flag,Enable TWI
    while (!(TWCR & (1<<TWINT)));// Wait till complete TWDR byte transmitted
	while((TWSR & 0xF8) != 0x28); // Check for acknoledgement
}

void TWI_stop()
{
	TWCR|=(1<<TWSTO)|(1<<TWINT)|(1<<TWEN); 
	 while (!(TWCR & (1<<TWSTO)));         // Wait till stop condition is transmitted
}	 
		








int main(void)
{   DDRB=0xff;
	//PORTB=0xff;
while (1)
{
	TWI_init_master();
	//PORTB=0xff;
	_delay_ms(20);
	master_start();
	//PORTB=0xff;
	_delay_ms(20);
	TWI_read_address(0x02);
	//PORTB=0xff;
	_delay_ms(20);
	TWI_write_data(0xff);
	//PORTB=0xff;
	_delay_ms(20);
	TWI_stop();
}

	
}
