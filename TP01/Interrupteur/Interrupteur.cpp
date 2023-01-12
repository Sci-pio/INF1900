#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
// Bouton interrupteur fait alterner la DEL dans l'ordre: rouge, vert, ambre.

bool debounce()
{
    if (PIND & 0x04)
    {
        _delay_ms(10);
        if (PIND & 0x04)
        {
            return true;
        }
    }
    return false;
}

int main()
{
    DDRA = 0xff;
    DDRD = 0x00;

    unsigned old_color = 0x02; // old_color: 2 = ambre, 1 = vert, 0 = rouge
    while (true)
    {
        if (debounce())
        {
            if (old_color == 0x02)
            {
                while (debounce())
                {
                    PORTA = 0x01; // rouge
                }
                old_color = 0x00;
            }
            else if (old_color == 0x00)
            {
                while (debounce())
                {
                    PORTA = 0x02;
                }
                old_color = 0x01;
            }
            else
            {
                while (debounce())
                {
                    PORTA = 0x01;
                    _delay_ms(5);
                    PORTA = 0x02;
                    _delay_ms(5);
                }
                old_color = 0x02;
            }
        }
        else
        {
            PORTA = 0x00;
        }
    }

    return 0;
}