#include "gra.h"

Gra::Gra(int ile_graczy, SOCKET * polaczenia, char * mapa)
{
	this->zerujObiekty();
	this->ile_graczy = ile_graczy;
	for(int i = 0; i < ile_graczy; i++)
	{
		this->gniazdka[i] = polaczenia[i];
	}
	////////////////////////////////////
	int ostatnie = MAP_SIZE*SZEROKOSC_POLA;
	int przedostatnie = (MAP_SIZE-1)*SZEROKOSC_POLA - 1 + 10;
	this->resp[0] = new Obiekt(0,30-1,0,30-1);
	this->resp[1] = new Obiekt(przedostatnie,ostatnie,przedostatnie,ostatnie);
	this->resp[2] = new Obiekt(0,30-1,przedostatnie,ostatnie);
	this->resp[3] = new Obiekt(przedostatnie,ostatnie,0,30-1);
	//////////////////////////////////
	for(int i = 0; i < ile_graczy; i++)
	{ 
		this->gracze[i] = new Gracz(0,0,0,0,POCZATKOWE_ZYCIE,W_MIEJSCU,PREDKOSC_CZOLGU, LICZBA_ZYC);
		respGracza(i);
	}
	this->wczytajMape(mapa);
	this->start();
}

void Gra::start()
{
	bool koniec_gry = false;
	while(!koniec_gry)
	{
		this->hashuj();
		for(int i = 0; i < this->ile_graczy; i++)
		{
			this->wyslijDoGracza(i);
		}
		//clock_t koniec = clock() + OPOZNIENIE * CLOCKS_PER_SEC / 1000.0;
		//while( clock() < koniec) continue;		
		Sleep(20);

		for(int i = 0; i < this->ile_graczy; i++)
		{
			this->odbierzOdGracza(i);
		}
		this->graj();
	}
}

void Gra::graj()
{
	for(int i = 0; i < ile_graczy; i++)
	{
		this->ruchGracza(i);
		if(this->gracze[i]->getX1() < 0 || this->gracze[i]->getY1() < 0 
			|| this->gracze[i]->getX2() > MAP_SIZE*SZEROKOSC_POLA
			|| this->gracze[i]->getY2() > MAP_SIZE*SZEROKOSC_POLA)
				this->gracze[i]->cofnij();
	}
}

void Gra::hashuj()
{
	int dlug = 0;
	for(int i = 0; i < MAP_SIZE * MAP_SIZE; i++, dlug++)
	{
		if(this->mur[i] != NULL)
			this->hash[i] = 'm';
		else if(this->sciany[i] != NULL)
			this->hash[i] = '0' + this->sciany[i]->getZycie();
		else
			this->hash[i] = '-';
	}
	hash[dlug++] = ile_graczy;
	for(int i = 0; i < ile_graczy; i++, dlug+=5)
	{
		hash[dlug] = gracze[i]->getX1() >> 8;
		hash[dlug+1] = gracze[i]->getX1();
		//int elo = 534;
		//char e1 = elo;
		//char e2 = elo >> 8;
		//int test = e1 + e2 * 256;
		hash[dlug+2] = gracze[i]->getY1() >> 8;
		hash[dlug+3] = gracze[i]->getY1();
		hash[dlug+4] = gracze[i]->getKierunek();
	}
	for(int i = 0; i < ile_graczy * LICZBA_POCISKOW; i++, dlug+=4)
	{
		if(pociski[i] != NULL)
		{
			hash[dlug] = pociski[i]->getX1() >> 8;
			hash[dlug+1] = pociski[i]->getX1();
			hash[dlug+2] = pociski[i]->getY1() >> 8;
			hash[dlug+3] = pociski[i]->getY1();
		}
		else
		{
			hash[dlug] = 0;
			hash[dlug+1] = -1;
			hash[dlug+2] = 0;
			hash[dlug+3] = -1;
		}
	}
	hash[dlug] = '\0';
}

void Gra::wyslijDoGracza(int id_gracza)
{
	int dlug = strlen(hash);
	send (gniazdka[id_gracza], hash, 500, 0); 
}

void Gra::graczStrzela(int id_gracza)
{
	for(int i = 0; i < LICZBA_POCISKOW; i++)
	{
		if(this->pociski[id_gracza * LICZBA_POCISKOW + i] == NULL)
		{
			this->pociski[id_gracza * LICZBA_POCISKOW + i] = &(this->gracze[id_gracza]->strzelaj());
			break;
		}
	}
}

void Gra::odbierzOdGracza(int id_gracza)
{
	char buf[80];
	if( recv(gniazdka[id_gracza], buf, 80, 0) > 0)
	{
		char ruch = buf[0];
		switch(ruch)
		{
			case 'w':
				this->gracze[id_gracza]->setKierunek(GORA);
				break;
			case 'a':
				this->gracze[id_gracza]->setKierunek(LEWO);
				break;
			case 's':
				this->gracze[id_gracza]->setKierunek(DOL);
				break;
			case 'd':
				this->gracze[id_gracza]->setKierunek(PRAWO);
				break;
			case 'q':
				this->graczStrzela(id_gracza);
		}
	}
}

void Gra::ruchGracza(int id_gracza)
{
	this->gracze[id_gracza]->ruszSie();
	for(int i = 0; i < MAP_SIZE * MAP_SIZE; i++)
	{
		if(this->mur[i] != NULL)
			if(this->gracze[id_gracza]->czyKolizja(*this->mur[i]))
				this->gracze[id_gracza]->cofnij();
	}
	for(int i = 0; i < MAP_SIZE * MAP_SIZE; i++)
	{
		if(this->sciany[i] != NULL)
			if(this->gracze[id_gracza]->czyKolizja(*this->sciany[i]))
				this->gracze[id_gracza]->cofnij();
	}
	for(int i = 0; i < ile_graczy; i++)
	{
		if(i != id_gracza)
			if(this->gracze[id_gracza]->czyKolizja(*this->gracze[i]))
				this->gracze[id_gracza]->cofnij();
	}
}

void Gra::ruchPociskow()
{

	for(int i = 0; i < LICZBA_POCISKOW * this->ile_graczy; i++)
	{
		if(this->pociski[i] != NULL)
		{
			this->pociski[i]->ruszSie();
			for(int j = 0; j < MAP_SIZE * MAP_SIZE; j++)
			{
				if(this->mur[j] != NULL)
					if(this->pociski[i]->czyKolizja(*this->mur[i]))
					{
						this->gracze[i]->setZycie(0);
						break;
					}
			}
			for(int j = 0; j < MAP_SIZE * MAP_SIZE; j++)
			{
				if(this->sciany[j] != NULL)
					if(this->pociski[i]->czyKolizja(*this->sciany[j]))
					{
						this->pociski[i]->setZycie(0);
						this->sciany[j]->setZycie(this->sciany[j]->getZycie() - 1);
						break;
					}
			}
			for(int j = 0; j < ile_graczy; j++)
			{
				if(this->pociski[i]->czyKolizja(*this->gracze[j]))
				{
					this->pociski[i]->setZycie(0);
					this->gracze[j]->setZycie(this->gracze[j]->getZycie() - 1);
					break;
				}
			}
			if(this->pociski[i]->czyZniszczono())
			{
				delete this->pociski[i];
				this->pociski[i] = NULL;
			}
		}
	}
}

void Gra::respGracza(int id_gracza)
{
	this->gracze[id_gracza]->setX1(this->resp[id_gracza]->getX1());
	this->gracze[id_gracza]->setX2(this->resp[id_gracza]->getX2());
	this->gracze[id_gracza]->setY1(this->resp[id_gracza]->getY1());
	this->gracze[id_gracza]->setY2(this->resp[id_gracza]->getY2());
	this->gracze[id_gracza]->setZycie(POCZATKOWE_ZYCIE);
}

void Gra::zerujObiekty()
{
	for(int i = 0; i < MAP_SIZE * MAP_SIZE; i++)
	{
		this->mur[i] = NULL;
		this->sciany[i] = NULL;
	}
	for(int i = 0; i < MAX_LICZBA_GRACZY * LICZBA_POCISKOW; i++)
	{
		this->pociski[i] = NULL;
	}
}

void Gra::wczytajMape(char * mapa)
{
	for(int i = 0; i < MAP_SIZE * MAP_SIZE; i++)
	{
		if(this->mur[i] != NULL)
		{
			delete this->mur[i];
			this->mur[i] = NULL;
		}
		if(this->sciany[i] != NULL)
		{
			delete this->sciany[i];
			this->sciany[i] = NULL;
		}
	}
	for(int i = 0; i < MAP_SIZE; i++)
	{
		for(int j = 0; j < MAP_SIZE; j++)
		switch(mapa[i*MAP_SIZE + j])
		{
			// MUR
			case 'm':
				this->mur[i*MAP_SIZE + j] = new Obiekt(i * SZEROKOSC_POLA, (i+1)*SZEROKOSC_POLA-1, j * SZEROKOSC_POLA, (j+1)*SZEROKOSC_POLA-1);
				break;
				// SCIANA
			case 's':
				this->sciany[i*MAP_SIZE + j] = new Zniszczalny(i * SZEROKOSC_POLA, (i+1)*SZEROKOSC_POLA-1, j * SZEROKOSC_POLA, (j+1)*SZEROKOSC_POLA-1,3);
				break;
		}
	}
}