// Win32CbV.cpp : Defines the entry point for the console application.
//

#pragma comment(lib, "Ws2_32.lib")

#include <Windows.h>
#include <winsock.h>
#include <iostream>
#include "gra.h"


HWND nextWnd = 0;
int counter = 0;
bool monitoring = true;

int msgcnt = 0;

int main()
{
	const int LICZBA_GRACZY = 2;
	WSADATA wsas;
	int result;
	WORD wersja;
	wersja = MAKEWORD(1, 1);
	result = WSAStartup(wersja, &wsas);

	SOCKET s;
	s = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in sa;
	memset((void *)(&sa), 0, sizeof(sa));
	sa.sin_family = AF_INET;
	sa.sin_port = htons(1337);
	sa.sin_addr.s_addr = htonl(INADDR_ANY);

	result = bind(s, (struct sockaddr FAR*)&sa, sizeof(sa));

	result = listen(s, 5);

	SOCKET si[LICZBA_GRACZY];

	struct sockaddr_in sc;
	int lenc;
	lenc = sizeof(sc);
	si[0] = accept(s, (struct sockaddr FAR *) &sc, &lenc);
	si[1] = accept(s, (struct sockaddr FAR *) &sc, &lenc);
	
	Gra gra1(2,si,"dddwdddddcllddccwddmddlllddddddddddddddddwddcccccdcdwdwddcdmdcdwwmdlllcmmmcdllddlddcdmdcddlddlddcmdmcddcdmdldcdddcddcmdddlcccccdddddddddddddmmmccmdmcccddmmmdcdddcdcddddd");
	closesocket(si[0]);
	closesocket(si[1]);
	
	
}
