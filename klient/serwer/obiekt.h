#pragma once

class Obiekt
{
	protected:
		int x1, x2;
		int y1, y2;
	public:
		Obiekt(int x1, int x2, int y1, int y2);
		int getX1();
		int getX2();
		int getY1();
		int getY2();
		void setX1(int x1);
		void setX2(int x2);
		void setY1(int y1);
		void setY2(int y2);
		bool czyKolizja(Obiekt & ob);
};