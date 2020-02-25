/**@file
*\brief Plik zawiera funkcje kluczowe do wykonania algorytmu Dijkstry i znalezienia o ile istnieje drogi z A do B.
*\author Tomasz Skowron
*\see pathfinding.cpp
*/

#ifndef pathfinding_H
#define pathfinding_H 

#include "Mapheader.h"
#include <string>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

/**
*\brief Funkcja inicjalizuje liste (tablice) pathtab na podstawie wierzcholkow struktuy mapy.
*@warning Wartosci domyslne elelentow listy to: new pathtab{ pHeadN,0,nullptr,false,nullptr }
*@param pName - wskaznik na strukture mapy
*@param path - wskaznik na pathtab do utworzenia
*@return path - wskaznik na zainicjalizowana tablice
*@return nullptr -jesli pName bylo puste
*/
pathtab * initialize(lcities *& pName, pathtab *& path);

/**
*\brief Funkcja odnajduje i zwraca wskaznik na element z tablicy pathtab, ktory wskazuje na miasto o zadanej nazwie.
*@warning Nie wolno szukac elementow ktore nie istnieja, szczegolnie jesli wywolujemy to z funkcji findshortAB().
*@param path - wskaznik na tablice pathtab
*@param cityA - nazwa szukanego miasta
*@return element - wskaznik na szukany element tablicy pathtab
*@return nullptr - gdy nie odnaleziono elementu
*/
pathtab * findinpath(pathtab *& path, const string & cityA);

/**
*\brief Funkcja odnajduje i zwraca wskaznik na element ze struktury mapy, ktory wskazuje na miasto o zadanej nazwie.
*@warning Funkcja moze zglosic wyjatek noroute, gdyz jesli szukamy jakiejs drogi, a miasto nie isnieje to nie mozna kontynuowac poszukiwan.  findinpath jest zatem niemal bezuzyteczna poza findshortAB().
*@param pName - wskaznik na tablice pathtab
*@param cityA - nazwa szukanego miasta
*@return element - wskaznik na szukany element mapy
*@exception noroute - gdy nie odnaleziono elementu
*/
lcities * findiname(lcities *& pName, const string & cityA);

/**
*\brief Funkcja znajduje w tablicy pathtab wskaznik na minimalna wartosc wiercholka, co jest jednym z kloczowych krokow algorytmu Dijksty.
*@warning Minimimum moze okazac sie nieskonczonoscia, czyli 0. Funkcja pomija miasto A oraz miasta odwiedzone, wiec jesli wszystkie byly odwiedzone to zwroci wartosc poczatku tablicy pathtab. \n Findmin porownoje wagi (value, czyli sdist), a nie dystanse ze struktury mapy!
*@param path - wskaznik na pathtab 
*@param cityA - nazwa miasta do ignorowania (wynika to z algorytmu Dijkstry, gdzie do miasta pczatkowego nie wracamy)
*@return min - wskaznik na minimalny pod wzgledem sdist i zgodny z algorytmem element tablicy pathtab
*@exception noroute gdy miasto nie istnieje
*/
pathtab *findmin(pathtab *& path, const string &cityA);

/**
*\brief Funkcja sprawdza czy jest istniejacy elemeny tablicy pathtab, ktory nie byl nigdy odwiedzony
*@param path - wskaznik na tablice pathtab
*@param cityA - nazwa miasta do ignorowania (wynika to z algorytmu Dijkstry, gdzie do miasta pczatkowego nie wracamy), a swoja droga w prawie wszystkich przypadkach to miasto jest juz odwiedzone.
*@return element - wskaznik na szukany element mapy
*@exception noroute - gdy nie odnaleziono elementu
*/
bool allvisited(pathtab *& path, const string & cityA);

/**
*\brief Funkcja wypelnia tablice pathtab wagami odleglosci punktu B od A.
*@warning Wagi nie sa rownie odleglosciom |X-Y|, tylko |A-X|+|X-Y|. Aby miec w tablicy odleglosci miedzy poszczegolnymi wierzcholkami nalezy ja podac funkcji weightless()
*@param pName - wskaznik na strukture mapy
*@param cityA - nazwa miasta A
*@param cityB - nazwa miasta B
*@param path - wkaznik na tablice pathtab
*@return path - uzupelniona wagami tablica pathtab
*@exception earlyhit - jesli droga zostala znaleziona wczesniej, niz odwiedzenie wszystkich miast przez Dijkstre 
*@exception noroute - jesli nie istnieje zadna droga z miata A
*@warning Mozna sobie pozwolic na earlyhit, nawet w strukturze mapy rozdzielnej, gdzie nie kazda droge mozna osiagnac, \n gdyz przejscie do nieosiagalnej czesci mapy jest ostatecznocia ograniczana przez findmin, a jesli tak sie stalo to alloradexist ponownie zabezpiecza niepoprawny wynik.
*/
pathtab findshortAB(lcities *& pName, const string & cityA, const string cityB, pathtab *& path);

/**
*\brief Sprawdza czy w strukturze ldirect istnieje element wskazujacy na miasto o zadanej nazwie.
*@param pVisited - wskaznik na strukture ldirect
*@param city - nazwa szukanego miasta
*@return true - gdy istnieje
*@return false - gdy nie istnieje
*@exception earlyhit - gdy droga moze byc znaleziona wczesniej
*/
bool existV(ldirect *& pVisited, const string & city);

/**
*\brief Sprawdza czy w strukturze mapy wystepuje droga z A do B.
*Ta funkcja rozni sie od existroad, gdyz sprawdza wylacznie istnienie i nie zwraca gdzie wystapily. \n Stworzone dla funkcji allroadexist().
*@param cityA - nazwa szukanego miasta A
*@param cityB - nazwa szukanego miasta B
*@param pName - wskaznik na strukture mapy
*@return true - gdy istnieja oba
*@return false - gdy nie istnieje conajmniej jedno z miast
*/
bool existroadAtoB(const string & cityA, const string & cityB, lcities *& pName);

/**
*\brief Sprawdza czy drogi miedzy wierzcholkami (vertex), a poprzednimi wierzcholkami (pvertex) w strukturze ldirect istnieja w strukturze mapy.
*@warning Wystarcza jedna nie isniejaca droga by zwrocono false.
*@param pVisited - wskaznik na strukture trasy
*@param pName - wskaznik na strukture mapy
*@param startcity - wskaznik na miasto poczatkowe, z ktorego droge szukamy. Pozwala na wczesniejsze przerwanie zakonczenia dzialania funkcji.
*@return true - gdy istnieja wszystkie drogi
*@return false - gdy nie istnieje conajmniej jedno z miast na trasie
*/
bool allroadexist(ldirect *& pVisited, lcities *& pName, const string & startcity);

/**
*\brief Funkcja wypelnia strukture ldirect trasami a punktu A do B na podstawie wartosci vertex i pvertex z tablicy pathtab.
*@param path - wskaznik na tablice pathtab
*@param cityA - nazwa miasta A
*@param cityB - nazwa miasta B
*@param pName - wskaznik na strukture mapy
*@return pVisited - struktura zawierajaca intersujaca nas droge z A do B
*@return nullptr - w wypadku niepowodzenia/przerwania petli
*@exception noroute - gdy funkcja otrzyma sygnal, ze droga nie istnieje
*/
ldirect * interpret(pathtab *&path, const string & cityA, const string & cityB, lcities*& pName);

/**
*\brief Odnajduje w strukturze ldirect element o zadanej nazwie.
*@warning Funkcja nie wypisuje dystansu z A do B, tylko poszczegolne dystanse z tablicy pathtab. Poleca sie uzycie weightless na tablicy pathtab by otrzymac poprawne dane, z |X-Y|, a nie |A-X|+|X-Y|. 
*\see wieghtless
*\see findshortAB
*@param pVisited - wskaznik na strukture trasy z A do B
*@param city - nazwa szukanego miasta 
*@return pHeadV - wskaznik na szukany element
*@return nullptr - gdy miasto nie istnieje w strukturze
*/
ldirect * findinvisited(ldirect*& pVisited, const string & city);

/**
*\brief Funkcja wypisuje do zadanego strumienia droge z A do B.
*@param route - wskaznik na strukture trasy
*@param stream - strumien wyjsciowy do zapisu
*@return void
*/
void writeroute(ldirect *& route, ostream & stream);

/**
*\brief Funkcja przywroci dystanse z |X-Y| usuwajac odleglosc |A-X|, powstale w wyniku algorytmu Dijkstry.
*@param route - wskaznik na strukture trasy z A do B
*@param endcity - nazwa miasta koncowego
*@param startcity - wskaznik na miasto poczatkowe
*@return void
*/
void weightless(ldirect *& route, const string & endcity, const string & startcity);

/**
*\brief Funkcja zbiera wage nadana przez findshortAB do sdist w elemencie wskazujacym na szukana nazwe miasta.
*@warning Szczegolnie dobym uzyciem tej funkcji jest zebranie odleglosci z A do B przez uzyciem weightless na tablicy pathtab, daje to gotowa sume dystansow. \n Droga z A do B musi istniec.
*@param path - wskaznik na tablice pathtab
*@param city - nazwa miasta o szukanej wadze
*@return value - waga odleglosci
*@return 0 - gdy waga jest nie mozliwa do odnalezienia
*/
double getweight(pathtab *& path, const string & city);

#endif
