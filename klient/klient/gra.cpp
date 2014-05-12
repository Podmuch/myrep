#include "gra.h"

Gra::Gra(char * ip, int port)
{
	okno = new sf::RenderWindow(sf::VideoMode(520, 520), "Tanks");
	strcpy(this->ip, ip);
	this -> port = port;
	czolg_tekstura.loadFromFile("czolg.jpg");
	czolg1_tekstura.loadFromFile("czolg1.jpg");
	czolg2_tekstura.loadFromFile("czolg2.jpg");
	czolg3_tekstura.loadFromFile("czolg3.jpg");
	mur_tekstura.loadFromFile("mur.jpg"); 
	sciana_tekstura3.loadFromFile("sciana.jpg");
	sciana_tekstura2.loadFromFile("sciana2.jpg");
	sciana_tekstura1.loadFromFile("sciana1.jpg");
	pocisk_tekstura.loadFromFile("pocisk.jpg");
	czolg_obrazek.setTexture(czolg_tekstura);
	czolg1_obrazek.setTexture(czolg1_tekstura);
	czolg2_obrazek.setTexture(czolg2_tekstura);
	czolg3_obrazek.setTexture(czolg3_tekstura);
	mur_obrazek.setTexture(mur_tekstura);
	sciana_obrazek.setTexture(sciana_tekstura1);
	pocisk_obrazek.setTexture(pocisk_tekstura);
	if (this->nowaGra())
	{
		printf("\npolaczono.\n Gra zostanie uruchomiona gdy polacza sie pozostali gracze");
		this->Graj();
	}
	else {
		printf("\nnie udalo sie polaczyc z serwerem");
	}
}

bool Gra::nowaGra()
{
	wersja = MAKEWORD(2,0); 
	WSAStartup(wersja, &wsas); 
	s = socket(AF_INET, SOCK_STREAM, 0); 
	memset((void *)(&sa), 0, sizeof(sa)); 
	sa.sin_family = AF_INET; 

	//int stary_port = 1337;
	//int nowy_port = 19309;

	sa.sin_port = htons(port); 
	sa.sin_addr.s_addr = inet_addr(this->ip); 
	int result; 
	result = connect(s, (struct sockaddr FAR *) &sa, sizeof(sa)); 
	if (result == SOCKET_ERROR) 
	{ 
		return false; // blad polaczenia
	} 
	int dlug; 
	char buf[7] = "gracz"; 
	dlug = strlen(buf);
	buf[dlug-1] = '\0'; 
	send (s, buf, dlug, 0); 
	return true;
}

bool Gra::odbierz()
{
	if(recv(s, hash, 500, 0) > 0)
		return true;
	return false;
}

bool Gra::wyslij(char akcja)
{
	char buf[2];
	int dlug = 2;
	buf[0] = akcja;
	buf[1] = '\0'; 
	send (s, buf, dlug, 0); 
	return false;
}

void Gra::wyswietl()
{
	int dlug = 0;
	for(int i = 0; i < MAP_SIZE; i++)
	{
		for(int j = 0; j < MAP_SIZE; j++)
		{
			dlug++;
			switch(hash[i*MAP_SIZE + j])
			{
				case 'm': 
					this->mur_obrazek.setPosition(j*SZEROKOSC_POLA,i*SZEROKOSC_POLA);
					okno->draw(this->mur_obrazek);
					break;
				case '3':
					this->sciana_obrazek.setTexture(sciana_tekstura3,true);
					this->sciana_obrazek.setPosition(j*SZEROKOSC_POLA, i*SZEROKOSC_POLA);
					okno->draw(this->sciana_obrazek);
					break;
				case '2':
					this->sciana_obrazek.setTexture(sciana_tekstura2, true);
					this->sciana_obrazek.setPosition(j*SZEROKOSC_POLA, i*SZEROKOSC_POLA);
					okno->draw(this->sciana_obrazek);
					break;
				case '1':
					this->sciana_obrazek.setTexture(sciana_tekstura1, true);
					this->sciana_obrazek.setPosition(j*SZEROKOSC_POLA,i*SZEROKOSC_POLA);
					okno->draw(this->sciana_obrazek);
					break;
			}
		}
	}
	ile_graczy = hash[dlug++];
	for(int i = 0; i < ile_graczy; i++, dlug+=5)
	{
		int x = hash[dlug] * 256 + (unsigned char)hash[dlug+1]; 
		int y = hash[dlug+2] * 256 + (unsigned char)hash[dlug+3];
		int kierunek = hash[dlug+4];
		switch(kierunek)
		{
		case 1:
			this->czolg1_obrazek.setPosition(x,y);
			okno->draw(this->czolg1_obrazek);
			break;
		case 2:
			this->czolg2_obrazek.setPosition(x,y);
			okno->draw(this->czolg2_obrazek);
			break;
		case 3:
			this->czolg3_obrazek.setPosition(x,y);
			okno->draw(this->czolg3_obrazek);
			break;
		default:
			this->czolg_obrazek.setPosition(x,y);
			okno->draw(this->czolg_obrazek);
		}
	}
	for(int i = 0; i < ile_graczy * 5; i++, dlug+=4)
	{
		int x = hash[dlug] * 256 + (unsigned char)hash[dlug+1]; 
		int y = hash[dlug+2] * 256 + (unsigned char)hash[dlug+3];
		if(x > 0)
		{
			this->pocisk_obrazek.setPosition(x,y);
			okno->draw(this->pocisk_obrazek);
		}
	}
}

void Gra::Graj()
{
    while (okno->isOpen())
    {
		if(this->odbierz())
		{
			char akcja = '0';
			sf::Event event;
			while (okno->pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					okno->close();
				if (event.type == sf::Event::KeyPressed)
				{
					if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
						akcja = 'a';
					if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
						akcja = 'd';
					if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
						akcja = 'w';
					if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
						akcja = 's';
					if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
						akcja = 'q';
				}
			}
			okno->clear();
			this->wyswietl();
			okno->display();
			this->wyslij(akcja);
		}
    }
}
