#include <SFML/Graphics.hpp>
#include "Pocisk.h"
using namespace sf;

#ifndef Gracz_h
#define Gracz_h
class Gracz{
private:
	Texture texczolg;
public:
	int X, Y;
	Sprite czolg;
	Gracz(int nr){
		if (!texczolg.loadFromFile("sprite.jpg")) printf("blad ladowania tekstury\n");
		czolg.setTexture(texczolg);
		czolg.setTextureRect(IntRect(0/*+26 %206*/, nr*26, 25, 25));
		X = 320;
		Y = 380;

	}
	void rysujgracza(RenderWindow &window){
		czolg.setPosition(X-12,Y-12);
		window.draw(czolg);
	}
	void ruch(Event &event){
		switch (event.key.code){
		case Keyboard::Up:
			Y--;
			if (czolg.getRotation() == 0 || czolg.getRotation() == 90) Y += 25;
			if (czolg.getRotation() == 180 || czolg.getRotation() == 90) X -= 25;
			czolg.setRotation(270);
			break;
		case Keyboard::Down:
			Y++;
			if (czolg.getRotation() == 180 || czolg.getRotation() == 270) Y -= 25;
			if (czolg.getRotation() == 0 || czolg.getRotation() == 270) X += 25;
			czolg.setRotation(90);
			break;
		case Keyboard::Left:
			X--;
			if (czolg.getRotation() == 90 || czolg.getRotation() == 0) Y += 25;
			if (czolg.getRotation() == 270 || czolg.getRotation() == 0) X += 25;
			czolg.setRotation(180);
			break;
		case Keyboard::Right:
			X++;
			if (czolg.getRotation() == 270 || czolg.getRotation() == 180) Y -= 25;
			if (czolg.getRotation() == 90 || czolg.getRotation() == 180) X -= 25;
			czolg.setRotation(0);
			break;
		}
	}
	Pocisk *strzal(){
		Pocisk *nowy=NULL;
		if (czolg.getRotation() == 0)  nowy=new Pocisk(X + 17, Y , 'r');
		if (czolg.getRotation() == 90) nowy = new Pocisk(X -25, Y + 17, 'd');
		if (czolg.getRotation() == 180) nowy = new Pocisk(X-42, Y-25, 'l');
		if (czolg.getRotation() == 270) nowy = new Pocisk(X, Y-42, 'u');
		return nowy;
	}
};
#endif