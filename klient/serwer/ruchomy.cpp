#include "ruchomy.h"

void Ruchomy::rusz(int kierunek)
{
	switch(kierunek)
	{
		case 0:
			y1-=predkosc;
			y2-=predkosc;
			break;
		case 1:
			x1+=predkosc;
			x2+=predkosc;
			break;
		case 2:
			y1+=predkosc;
			y2+=predkosc;
			break;
		case 3:
			x1-=predkosc;
			x2-=predkosc;
			break;
	}
}

Ruchomy::Ruchomy(int x1, int x2, int y1, int y2, int zycie, int kierunek, int predkosc) :
	Zniszczalny(x1,x2,y1,y2,zycie)
{
	this->kierunek = kierunek;
	this->predkosc = predkosc;
}

void Ruchomy::ruszSie()
{
	this->rusz(kierunek);
}

void Ruchomy::cofnij()
{
	this->rusz((kierunek + 2) % 4);
	//this->kierunek = 4;
}

int Ruchomy::getKierunek()
{
	return kierunek;
}

int Ruchomy::getPredkosc()
{
	return predkosc;
}

void Ruchomy::setKierunek(int kierunek)
{
	this->kierunek = kierunek;
}

void Ruchomy::setPredkosc(int predkosc)
{
	this->predkosc = predkosc;
}
