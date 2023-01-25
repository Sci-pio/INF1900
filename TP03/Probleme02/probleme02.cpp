#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay_basic.h>
#include <util/delay.h>
#include <math.h>

void init()
{
    DDRD = 0xFF;
    // PORTD = 0x01;
    // _delay_ms(3000);
}

// Dure 2sec
void generate60Hz(uint16_t pwd)
{

    uint16_t b = 16666;
    uint16_t d = 166;
    uint16_t a = d * pwd;
    uint16_t c = b - a;

    for (uint16_t i = 0; i < 120; i++) // chaque boucle dure 16 666 us, * 120 = 2s
    {
        PORTD = 0x01;

        for (uint16_t i = 0; i < a ; i += 2)
        {
            _delay_us(2);
        }

        PORTD = 0x00;

        for (uint16_t i = 0; i < c; i += 2)
        {
            _delay_us(2);
        }
    }
}

int main()
{
    init();

    for (uint16_t pwd = 0; pwd <= 100; pwd += 25)
    {
        generate60Hz(pwd);
    }
}