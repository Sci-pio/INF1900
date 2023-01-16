/**
* Programme qui allume une DEl en vert pendant 2 secondes apres avoir appuye et relache un bouton-poussoir 3 fois
* Entree: D2 pour le controle du bouton poussoir
* Sortie: A0, A1 pour le controle de la DEL
* \file probleme1.cpp
* \authors Kamil Maarite et Mathieu Lavoie
* \date 27 Janvier 2023
* cree le 16 janvier 2023
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

enum class Couleur
{
    vert = 0x02,
    eteint = 0x00
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
            PORTA = Couleur::vert;
            _delay_ms(2000);
            PORTA = Couleur::eteint;
            nbreFoisAppuye = 0;
            etatPresent = Etat::etatInitial;
        }
        break;
        }
    }
}