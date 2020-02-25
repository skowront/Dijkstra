/**@file
*\brief Plik zawiera funkcje uzytkowe do dzialan na liscie pName, z naciskiem na stworzenie struktury mapy na podstawie danych z pliku wejsciowego.
*\author Tomasz Skowron
*\see Loading.cpp
*/
#ifndef Loading_H
#define Loading_H 

#include "Mapheader.h"
#include <string>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

/**
*\brief Funkcja odnajduje miasta i zwraca strukture existindex ze wskaznikami na szukane elementy o ile istnialy.
*@param pName - wskaznik na strukture mapy
*@param cityA - nazwa miasta A
*@param distance - dystans miedzy miastami
*@param cityB - nazwa miasta B
*@return existindex - struktura z informacjami o informacjach ktore sa juz w strukturze,i ktorych nie ma \see existindex
*/
existindex existroad(lcities *& pName, const string & cityA, double distance, const  string & cityB);

/**
*\brief Funkcja dodaje nowe miasto do struktury mapy, tzn lcities.
*@warning Funkcja nie sprawdza czy miasto istnieje i dla stabilnosci oraz poprawnosci dzialania programu powinno nie istniec w strukturze.
*@param pName - wskaznik na strukture mapy
*@param cityA - nazwa miasta A
*@return void
*/
void addcity(lcities *&pName, const string &cityA);

/**
*\brief Funkcja dodaje droge, tzn dystans miedzy miastami A B.
*Funkcja wymaga podania struktury existindex by uproscic proces poszukuwania wskaznikow na odpowiednie miasta, te zas sa dodawane do struktury existindex przez funkcje existroad.
*@warning Funkcja nie sprawdza czy miasta istnialy, ani czy drogi istnialy i dla stabilnosci oraz poprawnosci dzialania programu musza one istniec.
*@param pName - wskaznik na strukture mapy
*@param dist - dystans do dodania
*@param cityloc - struktura zawierajaca wskazniki na miasta, miedzy ktorymi wystepuje dystans
*@return void
*/
void addroad(lcities *&pName, double dist, existindex & cityloc);

/**
*\brief Funkcja jest medium do tworzenia struktury mapy.
*Funkcja pobiera linie z pliku i sprawdzajac ich poprawnosc tworzy strukture mapy. 
*@param pName - wskaznik na strukture mapy
*@param infilename - sciezka do pliku wejsciowego z danymi do mapy
*@return void
*@exception nominusd -throw, gdy byl blad pliku wejsciowego
*@exception maplineerr - blad w linii w pliku
*@exception wasdiffrentdist - byl juz podany inny dystans
*/
void loadroad(lcities*& pName, const string &infilename);

#endif
