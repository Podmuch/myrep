#pragma once

#include "zniszczalny.h"

class Ruchomy : public Zniszczalny
{
	protected:
		int kierunek; // 0 - w; 1 - d; 2 - s; 3 - a;
		int predkosc;
	private:
		void rusz(int kierunek);
	public:
		Ruchomy(int x1, int x2, int y1, int y2, int zycie, int kierunek, int predkosc);
		void ruszSie();
		void cofnij();
		int getKierunek();
		int getPredkosc();
		void setKierunek(int kierunek);
		void setPredkosc(int predkosc);
};