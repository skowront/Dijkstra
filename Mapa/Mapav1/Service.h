/** @file 
*\brief Zawiera funkcje dla main(), do obslugi wprowadzanych danych, czy to w postaci argumentow linii polecen, czy danych bezposrednio z pliku.
*\author Tomasz Skowron
*\see Service.cpp
*/
#ifndef Service_H
#define Service_H 

#include "Mapheader.h"
#include <string>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

/**
*\brief Funkcja wypisuje na ekranie okno pomocy.
*@return void
*/
void printhelp();

/**
*\brief Funkcja sprawdza poprawnosc parametrow.
*@param ifpath - sciezka do pliku wejsciowego
*@param ofpath - sciezka do pliku wyjsciowego
*@param rfpath - sciezka do pliku z trasami
*@return true - zawsze true, o ile wczesniej nie bylo bledu krytycznego (brak pliku mapy, niepoprawnie otwarty/nie otwarty plik)
*@exception nominusd gdy nie ma pliku z mapa
*@exception noTnoO gdy nie ma ani pliku z trasami do wyznaczenia, ani pliku wyjsciowego
*@exception nominuso gdy nie ma pliku wyjsciowego
*@exception nominust gdy nie ma pliku z trasami do wyznaczenia 
*/
bool correctparams(const string &ifpath, const string &ofpath, const string & rfpath);

/**
*\brief Funkcja obsluguje podane argumenty z linii polecen, ustawia podane parametry na stan adekwatny do sytuacji.
*@param paramixmax -zmienna z iloscia parametrow
*@param params - tablica parametrow
*@param[out] mfpath - sciezka do pliku z mapa
*@param[out] ofpath - sciezka do pliku wyjsciowego
*@param rfpath - sciezka do pliku z trasami do wyznaczenia
*@param wasrf - (nie)byl plik z trasami
*@param wasof - (nie)byl plik wyjsciowy
*@return void
*/
void doparameters(int paramixmax, char*params[], string &mfpath, string &ofpath, string & rfpath, bool & wasrf, bool & wasof);

/**
*\brief Funkcja zaisuje do podanego strumienia wyjsciowego informacje o nieistniejacej drodze z A do B.
*@param outfile - strumien wyjsciowy
*@param cityA - miasto poczatkowe
a miasta A
*@param cityB - nazwa miasta B
*@return void
*/
void noroad(ostream & outfile, const string & cityA, const string cityB);

/**
*\brief Funkcja obsluguje podane argumenty z linii polecen, ustawia podane parametry na stan adekwatny do sytuacji.
*@param pName - wskaznik na strukture mapy
*@param path - wskaznik na strukture pathtab
*@param route - wskaznik na strukture ldirect, droge z A do B
*@param outfile - strumien wyjsciowy
*@param rfile - strumien wejsciowy z ktorego czytane sa poszukiwane trasy
*@return void
*/
void core(lcities *& pName, pathtab *& path, ldirect *& route, ostream & outfile, istream & rfile);

/**
*\brief Funkcja obsluguje wszystkie wyjatki ktore moga wystapic w programie.
*\see errorid
*@param excep - wyjatek (na podstawie wyliczenia errorid)
*@return - "nieznany  blad \n"
*@return - "blad pliku wejsciowego z mapa \n"
*@return - "inny dystans miedzy miastami zostal juz podany \n"
*@return - "droga nie istnieje \n"
*@return - "znaleziono trase"
*@return - "blad w linii w pliku z polaczeniami miedzy miastami \n"
*@return - "nie podano pliku z drogami \n"
*@return - "nie podano pliku z trasami do wyznaczenia \n"
*@return - "nie podano pliku wyjsciowego \n"
*@return - "blad pliku wyjsciowego \n"
*@return - "blad pliku z drogami do wyznaczenia \n"
*@return - "nie podano pliku z trasami, ani wyjsciowego \n"
*@return - ""
*/
string allexcep(errorid excep);

/**
*\brief Funkcja obsluguje tylko czesc wyjatkow specjalnie dla funkcji main.
*
*Funkcja moze zmienic wasrf lub/i wasof na podstawie braku podania ktoregos z parametrow do main.
*
*Obslugiwane wyjatki: noTnoO, nominust, nominuso
*@param excep - wyjatek (na podstawie wyliczenia errorid)
*@param wasrf - czy byl plik z trasami
*@param wasof - czy byl plik wyjsciowy
*@return - "nie podano pliku z trasami ani wyjsciowego"
*@return - "nie podano pliku z trasami do wyznaczenia"
*@return - "nie podano pliku wyjsciowego "
*\see main
*/
string mainexception(errorid  excep, bool & wasrf, bool & wasof);

#endif


