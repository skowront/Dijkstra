/** @file 
*Plik z glowna funkcja programu main().
*\author Tomasz Skowron
*/

// Mapav1.cpp : Defines the entry point for the console application.
//


#include "Mapheader.h"
#include "Valid.h"  
#include "Service.h"
#include "Cleanse.h"
#include "pathfinding.h"
#include "Loading.h"

#include <string>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

/**
*\brief Glowna funkcja programu 
*@warning W programie przyjeto nazwe mapa dla struktury z miastami i drogami, nie jest to tablica asocjacyjna.
*Funkcja wywoluje obsluge parametrow.
*Funkcja wywola w odpowiedni sposob funkcje core, zastepujac brakujace parametry standardowymi wyjsciami.
*Zostanie rowniez wywolane ladowanie struktury mapy z pliku.
*@warning funkcja moze zglosic wyjatek, ale zostanie on obsluzony w bloku catch na koncu main(), \n funkcja wylapuje rowniez wszystkie wyjatki spadajace do niej z podfunkcji.
*@param paramixmax -zmienna z iloscia parametrow
*@param params -tablica parametrow
*@return 0  
*/
int main(int paramixmax, char*params[])
{ 
	lcities * pName = nullptr;  //Poczatkowy element mapy
	pathtab * path = nullptr;	//Poczatkowy element tablicy do Dijkstry
	ldirect * route = nullptr;  //Poczatkowy element drogi (bez)posredniej
	fstream mapfile;  //strumien do pliku z drogami
	fstream routefile; //strumien do pliku z trasami do wyznaczenia
	ofstream outfile; //strumien do pliku wyjsciowgo
	string mfpath=""; //sciezka do pliku z drogami
	string rfpath=""; //sciezka do pliku z trasami
	string ofpath=""; //sciezka do pliku wyjsciowego
	bool wasrf = false; //czy byl plik z trasami
	bool wasof = false; //czy byl plik wyjsciowy
		try
		{
			try
			{
				doparameters(paramixmax, params, mfpath, ofpath, rfpath, wasrf, wasof);
			}
			catch (errorid excep)
			{
				cout << mainexception(excep, wasrf, wasof); //jesli ktorys z plikow niewymaganych nie zostal podany to zostanie wypisany komunikat i program wywola funkcje core z uzupelnieniem brakujacych wyjsc
			}
			mapfile.open(mfpath, ios::in);
			if (mapfile.good())
			{
				loadroad(pName, mfpath);
				if (wasrf == true && wasof == true)  //jesli byly pliki z drogami i wyjsciowy
				{
					outfile.open(ofpath);
					if (outfile.good()==true)
					{
						routefile.open(rfpath,ios::in);
						if (routefile.good() == true)
						{
							core(pName, path, route, outfile, routefile);
							routefile.close();
						}
						else
						{
							throw routeferr;  
						}
						outfile.close();
					}
					else
					{
						throw outferr;
					}
					throw donothing;
				}
				if (wasrf == false && wasof == true)  //jesli nie bylo pliku z trasami a byl wyjsciowy
				{
					outfile.open(ofpath);
					if (outfile.good())
					{
						core(pName, path, route, outfile, cin);
						outfile.close();
					}
					else
					{
						throw outferr;
					}
					throw donothing;
				}
				if (wasrf == true && wasof == false)  //jesli byl plik z trasami, a nie bylo pliku wyjsciowego
				{
					routefile.open(rfpath);
					if (routefile.good())
					{
						core(pName, path, route, cout, routefile);
						routefile.close();
					}
					else
					{
						throw routeferr;
					}
					throw donothing;
				}
				if (wasrf == false && wasof == false)  //jesli nie bylo pliku z trasami, ani pliku wyjsciowego
				{
				core(pName, path, route, cout, cin);
				}
			}
			else
			{
				throw nominusd;
			}
			complexclean(pName, 1, path, 0, route, 0);
		}
		catch (errorid excep)
		{
			cout << allexcep(excep); 
		}
	complexclean(pName, 1, path, 1, route, 1);
	mapfile.close();
	routefile.close();
	outfile.close();

	
    return 0;
}

