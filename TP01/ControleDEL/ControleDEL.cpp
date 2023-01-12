#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay_basic.h>
#include <util/delay.h>

int main()
{
    DDRA = 0xff; // A out
    
for (;;)
{
    PORTA=0x01;
    _delay_ms(500);
    PORTA=0x02;
    _delay_ms(500);
    for(int i = 0; i < 70; i++)
    {
    PORTA=0x01;
    _delay_ms(5);
    PORTA=0x02;
    _delay_ms(5);
    }
}
return 0;
}

