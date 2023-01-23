/**
 * Programme qui allume une DEL en vert pendant 2 secondes apres avoir appuye et relache un bouton-poussoir 3 fois.
 * Entree: D2 pour le controle du bouton poussoir
 * Sortie: A0, A1 pour le controle de la DEL
 * \file probleme02.cpp
 * \authors Kamil Maarite et Mathieu Lavoie
 * \date 27 Janvier 2023
 * Cree le 18 janvier 2023

 +--------------+--------+---------------+--------+-----------------------------+
| Etat Present | Entree | Prochain Etat | Sortie | Commentaire                 |
+--------------+--------+---------------+--------+-----------------------------+
| init         | 1      | ambre         | rouge  | 1 = appuye bouton-poussoir  |
+--------------+--------+---------------+--------+-----------------------------+
| ambre        | 0      | vert1         | ambre  | 0 = relache bouton-poussoir |
+--------------+--------+---------------+--------+-----------------------------+
| vert1        | 1      | rouge         | vert   |                             |
+--------------+--------+---------------+--------+-----------------------------+
| rouge        | 0      | eteint        | rouge  |                             |
+--------------+--------+---------------+--------+-----------------------------+
| eteint       | 1      | vert2         | eteint |                             |
+--------------+--------+---------------+--------+-----------------------------+
| vert2        | 0      | init          | vert   |                             |
+--------------+--------+---------------+--------+-----------------------------+

 */

#define F_CPU 8000000UL 

#include <avr/io.h>
#include <util/delay.h>
#define DDR_OUT 0xFF
#define DDR_IN 0x00
#define DEBOUNCE_TIME 10

enum class Etat
{
	init,
	ambre,
	vert1,
	rouge,
	eteint,
	vert2
};

enum Couleur_DEL
{
	eteint = 0x00,
	rouge = 0x01,
	vert = 0x02
};

bool estAppuye()
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

void initialiser()
{
	DDRA = DDR_OUT;
	DDRD = DDR_IN;
}

int main()
{
	initialiser();
	Etat etatPresent = Etat::init;
	while (true)
	{
		switch (etatPresent)
		{
		case Etat::init:
			PORTA = rouge;
			if (estAppuye())
			{
				etatPresent = Etat::ambre;
			}
			break;
		case Etat::ambre:
			PORTA = rouge;
			_delay_ms(5);
			PORTA = vert;
			_delay_ms(1);
			if (!estAppuye())
			{
				etatPresent = Etat::vert1;
			}
			break;
		case Etat::vert1:
			PORTA = vert;
			if (estAppuye())
			{
				etatPresent = Etat::rouge;
			}
			break;
		case Etat::rouge:
			PORTA = rouge;
			if (!estAppuye())
			{
				etatPresent = Etat::eteint;
			}
			break;
		case Etat::eteint:
			PORTA = eteint;
			if (estAppuye())
			{
				etatPresent = Etat::vert2;
			}
			break;
		case Etat::vert2:
			PORTA = vert;
			if (!estAppuye())
			{
				etatPresent = Etat::init;
			}
		}
	}
}