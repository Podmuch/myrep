#include "gra.h"
#include <iostream>
int main()
{
	printf("Czolgi\n");
	printf("Jezeli chcesz polaczyc sie z serwerem podaj ip: ");
	std::string ip;
	std::cin >> ip;
	printf("Podaj port: ");
	int port;
	std::cin >> port;
	Gra gra((char*)ip.c_str(), port);
    return 0;
}