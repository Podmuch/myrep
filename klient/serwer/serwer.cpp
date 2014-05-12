// Win32CbV.cpp : Defines the entry point for the console application.
//

#pragma comment(lib, "Ws2_32.lib")

#include <Windows.h>
#include <winsock.h>
#include <iostream>
#include <sqlite3.h>
#include <stdlib.h>
#include "gra.h"


HWND nextWnd = 0;
int counter = 0;
bool monitoring = true;
char mapa[170];
int msgcnt = 0;


static int callback(void *NotUsed, int argc, char **argv, char **azColName){
	int i=0;
	/*for (i = 0; i<argc; i++){
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");*/
	strcpy(mapa, argv[0]);
	return 0;
}

int main()
{
	sqlite3 *db;
	char *zErrMsg = 0;
	int  rc;
	char *sql;
	struct sockaddr_in sc;
	int lenc;
	const int LICZBA_GRACZY = 2;
	WSADATA wsas;
	int port;
	int result;
	WORD wersja;
	SOCKET s;
	struct sockaddr_in sa;
	SOCKET si[LICZBA_GRACZY];
	//inicjalizacja winsock
	wersja = MAKEWORD(1, 1);
	result = WSAStartup(wersja, &wsas);
	//pobranie nr portu
	//printf("Podaj numer portu na ktorym chcesz stworzyc serwer: ");
	//scanf("%d", &port);
	//stworzenie gniazdka nasluchujacego
	s = socket(AF_INET, SOCK_STREAM, 0);
	memset((void *)(&sa), 0, sizeof(sa));
	sa.sin_family = AF_INET;

	//int stary_port = 1337;
	//int nowy_port = 19309;

	//inicjalizacja i start serwera
	sa.sin_port = htons(1337);//port);
	sa.sin_addr.s_addr = htonl(INADDR_ANY);
	result = bind(s, (struct sockaddr FAR*)&sa, sizeof(sa));
	result = listen(s, 5);
	printf("serwer uruchomiony. Oczekiwanie na graczy: \n");

	//przyjmowanie graczy
	lenc = sizeof(sc);
	si[0] = accept(s, (struct sockaddr FAR *) &sc, &lenc);
	std::cout << "POLACZONO 1 gracza\n";
	si[1] = accept(s, (struct sockaddr FAR *) &sc, &lenc);
	std::cout << "POLACZONO 2 gracza\n";
	
	// Open database 
	rc = sqlite3_open("test.db", &db);
	if (rc){
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		exit(0);
	}
	else{
		fprintf(stdout, "Opened database successfully\n");
	}
	// Create SQL statement 
	sql = "SELECT ZAWARTOSC "  \
		"	FROM MAPY " \
		"	WHERE ID=1 ";
	// Execute SQL statement 
	rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
	if (rc != SQLITE_OK){
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	else{
		fprintf(stdout, "Mapa pobrana\n");
	}
	sqlite3_close(db);

	//dddwdddddcllddccwddmddlllddddddddddddddddwddcccccdcdwdwddcdmdcdwwmdlllcmmmcdllddlddcdmdcddlddlddcmdmcddcdmdldcdddcddcmdddlcccccdddddddddddddmmmccmdmcccddmmmdcdddcdcddddd
	//ddddddddddddddmmmmmmmmmmmddddddddddddddd1ddddddddd1dd2ddddddddd2dd3ddddd3dd33ddddddddddddddddddddddddddddmdmdmdmdmdmdddddddddddddddddddddddddddddddddddddddddmmmmmmmmmmmd
	Gra gra1(2,si,mapa);
	std::cout << "Rozpoczecie rozgrywki\n";
	closesocket(si[0]);
	closesocket(si[1]);
}

/*dodawanie elementow

sqlite3 *db;
char *zErrMsg = 0;
int  rc;
char *sql;
// Open database 
rc = sqlite3_open("test.db", &db);
if (rc){
	fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
	exit(0);
}
else{
	fprintf(stdout, "Opened database successfully\n");
}
//MAPY (ID, ZAWARTOSC)
// Create SQL statement 
sql = "SELECT *	"  \
"	FROM MAPY";
// Execute SQL statement 
rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
if (rc != SQLITE_OK){
	fprintf(stderr, "SQL error: %s\n", zErrMsg);
	sqlite3_free(zErrMsg);
}
else{
	fprintf(stdout, "Table created successfully\n");
}
sqlite3_close(db);
return 0;
*/