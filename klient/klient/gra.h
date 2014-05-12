#pragma once

#include <SFML/Graphics.hpp>
#include "obiekt.h"
#include <string.h>
#pragma comment(lib, "ws2_32.lib")
#include <WinSock.h>

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
		static const int IP_SIZE = 20;
		char ip[IP_SIZE];
		int ile_graczy, port;
		// socket //
		SOCKET s;
		struct sockaddr_in sa;
		WSADATA wsas; 
		WORD wersja; 
		sf::Texture czolg_tekstura, czolg1_tekstura, czolg2_tekstura, czolg3_tekstura, mur_tekstura, sciana_tekstura1, sciana_tekstura2, sciana_tekstura3, pocisk_tekstura;
		sf::Sprite czolg_obrazek,czolg1_obrazek,czolg2_obrazek,czolg3_obrazek,mur_obrazek,sciana_obrazek,pocisk_obrazek;
		char hash[500];
		sf::RenderWindow * okno;
	public:
		explicit Gra(char * ip, int port);
		bool nowaGra();
		bool odbierz();
		bool wyslij(char akcja);
		void Graj();
		void wyswietl();
};