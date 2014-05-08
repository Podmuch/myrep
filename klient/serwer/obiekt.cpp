#include "obiekt.h"

Obiekt::Obiekt(int x1, int x2, int y1, int y2)
{
	this->x1 = x1;
	this->x2 = x2;
	this->y1 = y1;
	this->y2 = y2;
}

int Obiekt::getX1()
{
	return x1;
}

int Obiekt::getX2()
{
	return x2;
}

int Obiekt::getY1()
{
	return y1;
}

int Obiekt::getY2()
{
	return y2;
}

void Obiekt::setX1(int x1)
{
	this->x1 = x1;
}

void Obiekt::setX2(int x2)
{
	this->x2 = x2;
}

void Obiekt::setY1(int y1)
{
	this->y1 = y1;
}

void Obiekt::setY2(int y2)
{
	this->y2 = y2;
}

bool Obiekt::czyKolizja(Obiekt & ob)
{

	if((this->x1 <= ob.x1 && this->x2 >= ob.x1 || this->x1 <= ob.x2 && this->x2 >= ob.x2 || 
		((this->x1 >= ob.x1 && this->x2 >= ob.x1) && (this->x1 <= ob.x2 && this->x2 <= ob.x2))) 
		&& 
		(this->y1 <= ob.y1 && this->y2 >= ob.y1 || this->y1 <= ob.y2 && this->y2 >= ob.y2 || 
		((this->y1 >= ob.y1 && this->y2 >= ob.y1) && (this->y1 <= ob.y2 && this->y2 <= ob.y2))))
			return 1;
	return 0;
}
