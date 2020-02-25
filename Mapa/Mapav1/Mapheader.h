/** @file */


#ifndef MAPHEADER_H   
#define MAPHEADER_H   

#include <string>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

/**
*\brief Struktura mapy zlozonej z drog jednokierunkowych.
*lcities to lista list.
*Struktura reprezentuje miasto. Miasta tworza liste jednokierunkowa. Kazdemu miastu przypisana jest droga lub lista drog wychodzacych do innych miast.
*/
struct lcities 
{

/**
*\brief Struktura dystansow w mapie.
*@warning Struktura dalej zwana mapa.
*ldist zdefiniowane w lcities, to struktura zawierajaca wartosc, interpretowana jako odleglosc lub droga o danym dystansie z miasta wskazujacego na ten element \n 
*do miasta, na ktory element wskazuje.
*Elementy tworza liste jednokierunkowa, ktora jest podwieszona do jakiegos miasta.
*@warning W tabeli X oznacza zupelnie dowolne miasto/miasta o n-tym/n-tych indeksie/indeksach. \n "...->V.X." to wskaznik na liste w dol tabeli \n "...->>>.." to wskaznik na nastepny element w wierszu tabeli. \n Struktura rzeczywista moze sie znaczaco roznic od przykladowej w niektorych przypadkach co do wartosci, ale nie co do konceptu.
*/
	struct ldist
	{
		/** odleglosc drogi miedzy miastami
		 */
		double dist = 0;//dystans zero oznacza ze droga nie istnieje
		/** wskaznik na miasto w do ktorego prowadzi droga
        */
		lcities * pNextCity = nullptr;
		/** wskaznik na nastepna droge wychodzaca z miasta
 		*/
      ldist * pNextDist = nullptr;
	};
	/** nazwa miasta **/
	string city; 
	/** wskaznik na nastepne miasto w liscie **/
	lcities * pNextCity = nullptr;
	/** wskaznik na pierwsza droge wychodzaca z listy 
    */
    ldist * pNextDist = nullptr;
};

/**
*\brief Struktura dla funkcji existroad, z informacjami o (nie)istnieniu miast oraz wskaznikach na nie.
*Struktura jest uzupelniana funkcja existroad, by stanowic podstawy do uzupelniania listy przy ladowaniu miast lub nie.
*/
struct existindex
{
	/** Czy istnieje miasto A */
	bool existA;
	/** Czy istnieje miasto B */
	bool existB;
	/** Czy dystans miedzy miastami A i B jest poprawny
	*@warning Wartosc tego elementu jest scisle okreslona. \n "0" - jesli taki dystans nie istnieje \n "1" - jesli dystans podany z pliku jest taki jak juz byl podany wczesniej \n "2" - jesli wczesniej podano inny dystans z A do B
	*/
	int correctdist;/**nodist=0=nie istnieje, okdist=1=taki sam, wasdiffrentdist=2=byl inny*/
	/** Wskaznik na miasto A jesli istnieje, nullptr jesli nie istnieje */
	lcities *locationptrA = nullptr;
	/** Wskaznik na miasto B jesli istnieje, nullptr jesli nie istnieje */
	lcities *locationptrB = nullptr;
};

/**
*\brief Struktura do podawania wag odleglosciowych i poprawnego wykonania algorytmu Dijkstry, dalej zwana pathtab.
*/
/*
*Struktura jest przykladem tabeli dla mapy o wierzcholkach A,X,..,B i szukanym dystansie z A do B. Kolejnosc rzedow nie ma znaczenia dla algorytmu i zalezy od kolejnosci miast w strukturze mapy.
*
*vertex oznacza miasto obecnie odwiedzone
*pvertex to miasto z ktorego drogi obecnie sa analizowane
*sdist to waga przypisana dla miasta
*visited odpowiada na pytanie czy zostalo odwiedzone
*nextpathtab nastepy rzad w tabeli
*/
/**
*@warning tablica pathtab jest twrzona dla wszystkich istniejacych wierzcholkow niezaleznie od jakiejkolwiek zmiennej, gdyz nie wiemy ile wierzcholkow (ani ktore) musi znalezc sie na trasie.
*/
struct pathtab
{
	/** Wskaznik na wiercholek */
	lcities * vertex = nullptr;
	/** Waga, czyli odleglosc do miasta X z miasta A, przez miasta Y,Z... */
	double sdist = 0;
	/** Wskaznik na wiercholek z ktorego przychodzi Dijkstra */
	lcities * pvertex = nullptr;
	/** Czy bylo odwiedzone */
	bool visited = false;
	/** Wskaznik na kolejny element listy/tabeli pathtab */
	pathtab * nextpathtab;
};

/**
*\brief Struktura drogi z A do B.
*Struktura wskazuje na elementy tablicy pathtab (pathtab), przez ktore nalezy isc aby dotrzec z miasta A do miasta B, a dokladniej z miasta B do miasta A, \n poniewaz funkcje poruszaja sie z vertex do pvertex poczynajac od vertex wskazujacy na miasto B.
*/
struct ldirect
{
	/** Wskaznik na miasto X */
	pathtab * vertex = nullptr;
	/** Wskaznik na nastepny element listy */
	ldirect * lvNext = nullptr;
};

/**
*\brief Wyliczenie wyjatkow programu.
*Zawiera wszystkie identyfikatory wszystkich wyjatkow, ktore pojawiaja sie w programie.
*/
enum errorid
{
	unknown, ///< 0 nieznany
	maperr, ///< 1 blad pliku mapy
	wasdiffrentdist, ///< 2 blad dystansu do existindex
	noroute, ///< 3 nie ma drogi
	earlyhit, ///< 4 znaleziono trase
	maplineerr, ///< 5 blad linii w mapie
	nominusd, ///< 6 brak pliku mapy
	nominust, ///< 7 brak pliku tras od wyznaczenia
	nominuso, ///< 8 brak pliku wyjsciowego
	outferr, ///< 9 blad pliku wyjsciowego
	routeferr, ///< 10 blad pliku z trasami do wyznaczenia
	noTnoO, ///< 11 nie podano ani pliku z trasami, ani wyjsciowego
	donothing, ///< 12 nie rob nic, koncz program
	nodist, ///< 13 nie ma drogi do existindex
	okdist, ///< 14 droga jest taka sama jak podana
};


#endif
