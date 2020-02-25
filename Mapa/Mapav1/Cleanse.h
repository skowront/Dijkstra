/** @file
*\brief Plik zawiera funkcje do usuwania struktur powstalych w wyniku dzialania programu.
*\author Tomasz Skowron
*\see Cleanse.cpp
*/
#ifndef Cleanse_H
#define Cleanse_H 

#include "Mapheader.h"
#include <string>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

/**
*\brief Funkcja usuwa liste obiektow typu lcities, z lista podrzedna obiektow ldist wlacznie.
*@param pName - wskaznik na strukture do usuniecia
*@return void
*/
void clean(lcities *& pName);

/**
*\brief Funkcja usuwa strukture typu ldirect.
*@param route - wskaznik na strukture do usuniecia
*@return void
*/
void cleanroute(ldirect *& route);

/**
*\brief Funkcja usuwa liste elementow typu pathtab.
*@param path - wskaznik na strukture do usuniecia
*@return void
*/
void cleanpath(pathtab *& path);

/**
*\brief Wywoluje usuwanie podanych struktur dwokrotnie, po strukturze nalezy podac 1/0 lub true false co decyduje o usuwaniu struktury dla true i pominieciu dla false.
*@warning Funkcja jest tylko medium do wywolania funkcji czyszczacych poszczegolne struktury. Wywoluje clean(), cleanroute(), cleanpath() w zaleznosci od parametrow typu bool.
*@param pName - wskaznik na strukture lcities
*@param pn - 1 usun, 0 nie usuwaj
*@param path - wskaznik na strukture lcities
*@param pt - 1 usun, 0 nie usuwaj
*@param route - wskaznik na strukture lcities
*@param rt - 1 usun, 0 nie usuwaj
*@return void
*/
void complexclean(lcities *& pName, bool pn, pathtab *&path, bool pt, ldirect * &route, bool rt);

#endif


