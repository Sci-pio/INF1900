/**
* Programme qui allume une DEl en vert pendant 2 secondes apres avoir appuye et relache un bouton-poussoir 3 fois
* Entree: D2 pour le controle du bouton poussoir
* Sortie: A0, A1 pour le controle de la DEL
* \file probleme1.cpp
* \authors Kamil Maarite et Mathieu Lavoie
* \date 27 Janvier 2023
* cree le 16 janvier 2023


+--------------+--------+---------------+--------+------------------------------------------------+
| Etat Present | Entree | Prochain Etat | Sortie | Commentaire                                    |
+--------------+--------+---------------+--------+------------------------------------------------+
| etatInitial  | 0      | etatInitial   | eteint | Entree vaut 1 SSI on a appuye-relache 3 fois   |
|              |        |               |        | le bouton-poussoir                             |
+--------------+--------+---------------+--------+------------------------------------------------+
| etatInitial  | 1      | etatAllume    | vert   |                                                |
+--------------+--------+---------------+--------+------------------------------------------------+
| etatAllume   | x      | etatInitial   | vert   | S'effectue automatiquement apres deux secondes |
+--------------+--------+---------------+--------+------------------------------------------------+
*/

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#define DDR_OUT 0xFF
#define DDR_IN 0x00
#define DEBOUNCE_TIME 10

bool filtrerRebond()
{
    if (PIND & 0x04)
    {
        _delay_ms(DEBOUNCE_TIME);
        if (PIND & 0x04)
        {
            return true;
        }
    }
    return false;
}

bool aEteAppuyeBouton()
{
    if (filtrerRebond())
    {
        while (filtrerRebond())
        {
            _delay_ms(5);
        }
        return true;
    }
    return false;
}

enum class Etat
{
    etatInitial,
    etatAllume
};

void initialiser()
{
    DDRA = DDR_OUT;
    DDRD = DDR_IN;
}

int main()
{
    initialiser();
    Etat etatPresent = Etat::etatInitial;
    int nbreFoisAppuye = 0;
    uint8_t vert = 0x02;
    uint8_t eteint = 0x00;

    while (true)
    {
        switch (etatPresent)
        {
        case Etat::etatInitial:
        {
            while (!aEteAppuyeBouton()){}
            nbreFoisAppuye++;
            if (nbreFoisAppuye == 3)
            {
                etatPresent = Etat::etatAllume;
            }
        }
        break;
        case Etat::etatAllume:
        {
            PORTA = vert;
            _delay_ms(1800); // correspond a environ 2s avec le temps d'execution
            PORTA = eteint;
            nbreFoisAppuye = 0;
            etatPresent = Etat::etatInitial;
        }
        break;
        }
    }
}