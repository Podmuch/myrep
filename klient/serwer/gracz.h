#pragma once

#include "ruchomy.h"

class Gracz : public Ruchomy
{
	private:
		int liczba_zyc;
	public:
		Gracz(int x1, int x2, int y1, int y2, int zycie, int kierunek, int predkosc, int liczba_zyc);
		Ruchomy & strzelaj();
};