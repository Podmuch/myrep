
#include "gracz.h"

Gracz::Gracz(int x1, int x2, int y1, int y2, int zycie, int kierunek, int predkosc, int liczba_zyc) :
	Ruchomy(x1,x2,y1,y2,zycie,kierunek,predkosc)
{
	this->liczba_zyc = liczba_zyc;
}
Ruchomy & Gracz::strzelaj()
{
	int x = x1 + (x2-x1) / 2 - 1;
	int y = y1 + (y2-y1) / 2 - 1;
	Ruchomy * pocisk;
	switch(kierunek)
	{
		case 0:
			pocisk = new Ruchomy(x,x+2,y1-3,y1-1,1,kierunek,predkosc*3);
			break;
		case 1:
			pocisk = new Ruchomy(x2+1,x2+3,y,y+2,1,kierunek,predkosc*3);
			break;
		case 2:
			pocisk = new Ruchomy(x,x+2,y2+1,y2+3,1,kierunek,predkosc*3);
			break;
		case 3:
			pocisk = new Ruchomy(x1-3,x1-1,y,y+2,1,kierunek,predkosc*3);
			break;
	}
	return *pocisk;
}