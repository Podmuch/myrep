#pragma once
#include "gracz.h"
#pragma comment(lib, "Ws2_32.lib")
#include <Windows.h>
#include <winsock.h>
#include <time.h>

class Gra 
{
	private:
		static const int OPOZNIENIE = 20;
		static const int MAP_SIZE = 13;
		static const int MAX_LICZBA_GRACZY = 4;
		static const int SZEROKOSC_POLA = 40;
		static const int POCZATKOWE_ZYCIE = 5;
		static const int PREDKOSC_CZOLGU = 1;
		static const int PREDKOSC_POCISKU = 3;
		static const int LICZBA_ZYC = 3;
		static const int LICZBA_POCISKOW = 5;
		enum { GORA = 0, PRAWO = 1, DOL = 2, LEWO = 3, W_MIEJSCU = 4 };
		int ile_graczy;
		Gracz * gracze[MAX_LICZBA_GRACZY];
		Ruchomy * pociski[MAX_LICZBA_GRACZY * LICZBA_POCISKOW];
		Zniszczalny * sciany[MAP_SIZE * MAP_SIZE];
		Obiekt * mur[MAP_SIZE * MAP_SIZE];
		char hash[500];
		Obiekt * resp[MAX_LICZBA_GRACZY];

		SOCKET gniazdka[MAX_LICZBA_GRACZY];

	public:
		Gra(int ile_graczy, SOCKET * polaczenia, char * mapa);
		void start();
		void graj();
		void hashuj();
		void wyslijDoGracza(int id_gracza);
		void odbierzOdGracza(int id_gracza);
		void ruchGracza(int id_gracza);
		void ruchPociskow();
		void wczytajMape(char * mapa);
		void respGracza(int id_gracza);
		void graczStrzela(int id_gracza);
		void zerujObiekty();
};