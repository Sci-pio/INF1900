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
  /*enum class Color = {
        ambre,
        vert = 0x02,
        rouge = 0x01,
        aucune = 0x00
        };*/

int main()
{
    DDRA = 0xff;
    DDRD = 0x00;

    /* Color oldColor = ambre;
    while(true)
    {
        if (debounce())
        {
            switch(oldColor)
            {
                case Color::ambre: 
                while(debounce())
                {
                    PORTA = rouge;
                }
                oldColor = rouge;
                break;

                case Color::rouge:
                while(debounce())
                {
                    PORTA = vert;
                }
                oldColor = vert;
                break;

                case Color::vert:
                while(debounce())
                {
                    PORTA = 0x01;
                    _delay_ms(5);
                    PORTA = 0x02;
                    _delay_ms(5);
                }
                oldColor = ambre;
                break;
            }
        }
        else
        {
            PORTA = Color::aucune;
        }
    }*/

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