#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay_basic.h>
#include <util/delay.h>
#include <math.h>

// cette fonction dure 1ms (x3000 iterations = 3s)
void generatePWM(uint16_t a)
{
    //uint16_t periodeFermee = 3000-a;
    uint16_t c = uint16_t(round(0.333*double(a))); 
    PORTA = 0x01;

    for (uint16_t i = 0; i<c; i++) // 
    //for (uint16_t i = 0; i<a; i++)
    {
        _delay_us(1);
    }

    PORTA = 0x00;
    for (uint16_t i = 0; i<(1000-c); i++)
    //for (uint16_t i = 0; i<periodeFermee; i++)
    {
        _delay_us(1);
    }
}

int main()
{
    DDRA = 0xff;
    //uint16_t b = 3000;

    for (int i = 3000; i>0; i--)
    {
        generatePWM(i);
    }
    PORTA = 0x00;
}