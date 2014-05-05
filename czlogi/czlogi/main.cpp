#include <SFML/Graphics.hpp>
#include "Mapa.h"
#include "Gracz.h"
#include "Pocisk.h"
using namespace sf;
using namespace std;



//mapa 25x27
int main()
{
	//wczytanie mapy
	Mapa mapa;
	mapa.wczytaniemapy(1);
	//wczytanie gracza
	Gracz gracz1(0);
	//tablica pociskow
	Pocisk *pociski[10];
	for (int i = 0; i < 10; i++){
		pociski[i] = NULL;
	}
	//okno gry
	RenderWindow window(VideoMode(640, 480), "Czolgi");
	//otoczka mapy 
	RectangleShape rectangle(Vector2f(625, 337));
	rectangle.setFillColor(Color(0, 0, 0, 0));
	rectangle.setOutlineColor(Color(0, 255, 0, 255));
	rectangle.setOutlineThickness(5);
	rectangle.setPosition(Vector2f(7, 53));
	//g³ówna petla programu
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::KeyPressed){
				gracz1.ruch(event, mapa);
				if (event.key.code == Keyboard::Space) {
					int i;
					for (i = 0; i < 10; i++){
						if (pociski[i] == NULL) {
							pociski[i] = gracz1.strzal();
							i = 12;
						}
					}
					if (i == 10) {
						delete pociski[0];
						for (i = 0; i < 9; i++){
							pociski[i] = pociski[i + 1];
						}
						pociski[i] = gracz1.strzal();
					}
				}
			}
		}
		window.clear();
		gracz1.rysujgracza(window);
		window.draw(rectangle);
		for (int i = 0; i < 10; i++){
			if (pociski[i] != NULL) {
				pociski[i]->ruch();
				pociski[i]->rysujpocisk(window);
				if (pociski[i]->kolizja(mapa)) {
					delete pociski[i];
					pociski[i] = NULL;	
				}
			}
		}
		mapa.rysowaniemapy(window);
		window.display();
	}
	return 0;
}