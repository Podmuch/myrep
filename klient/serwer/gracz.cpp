
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
	Ruchomy * pocisk = new Ruchomy(x,x+2,y,y+2,1,kierunek,predkosc);
	return *pocisk;
}