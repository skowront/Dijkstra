/**@file
*\brief Plik zawiera funkcje uzytkowe do dzialan na liscie pName, z naciskiem na stworzenie struktury mapy na podstawie danych z pliku wejsciowego.
*\author Tomasz Skowron
*\see Loading.cpp
*/

#include "Mapheader.h"
#include "Valid.h"  
#include "Service.h"
#include "Cleanse.h"
#include "pathfinding.h"
#include "Loading.h"

existindex existroad(lcities *& pName, const string & cityA, double distance, const  string & cityB)
{
	existindex existreturn = { false,false,nodist,nullptr };
	if (pName)
	{
		auto pHeadN = pName;
		auto pHeadD = pHeadN->pNextDist;
		while (pHeadN != nullptr)
		{

			if (pHeadN->city == cityA)
			{
				existreturn.existA = true;
				existreturn.locationptrA = pHeadN;
				if (pHeadN->pNextDist)
				{
					pHeadD = pHeadN->pNextDist;
					while (pHeadD != nullptr)
					{
						if (pHeadN->pNextCity)
						{
							if (pHeadN->pNextCity->city == cityB && pHeadD->dist == distance && pHeadD->dist != 0)
							{
								existreturn.correctdist = okdist;
							}
							if (pHeadN->pNextCity->city == cityB && pHeadD->dist == distance && pHeadD->dist == 0)
							{
								existreturn.correctdist = wasdiffrentdist;
							}
							else
							{
								pHeadD = pHeadD->pNextDist;
							}
						}
						else
						{
							break;
						}
					}
				}
			}
			if (pHeadN->city == cityB)
			{
				existreturn.existB = true;
				existreturn.locationptrB = pHeadN;
			}
				pHeadN = pHeadN->pNextCity;
		}
		return existreturn;
	}
	else
	{
		//cout << "no existing list given, creating first city" << endl;
		pName = new lcities{ cityA,nullptr,nullptr };
		existreturn.existA = true;
		existreturn.locationptrA = pName;
	}
	return existreturn;
}


void addcity(lcities *&pName, const string &cityA)
{
	auto pHead=pName;
	if (pName==nullptr)
	{
		pName = new lcities{cityA,nullptr,nullptr};
	}
	else
	{
		if (pHead->pNextCity)
		{
			while (pHead->pNextCity != nullptr&&pHead->pNextCity->city != cityA)
			{
				pHead = pHead->pNextCity;
			}
		}
		pHead->pNextCity= new lcities{ cityA,nullptr,nullptr };
	}
	return;
}


void addroad(lcities *&pName, double dist, existindex & cityloc)
{
	auto pHeadD = cityloc.locationptrA->pNextDist;
	if (pHeadD)
	{
		while (pHeadD->pNextDist != nullptr)
		{
			pHeadD = pHeadD->pNextDist;
		}
		pHeadD->pNextDist = new lcities::ldist{ dist,cityloc.locationptrB };
	}
	else
	{
		cityloc.locationptrA->pNextDist = new lcities::ldist{ dist,cityloc.locationptrB };
	}
	return;
}


void loadroad(lcities*& pName,const string &infilename)
{
	fstream inputfs;
	string cityA;
	string cityB;
	existindex check;
	string line = "";
	double distance;
	inputfs.open(infilename, ios::in);
	if (!inputfs.good())
	{
		throw nominusd;
	}
	while (getline(inputfs,line))
	{
		stringstream ssl(line);
		ssl >> cityA;
		ssl >> cityB;
		ssl >> distance;
		check=existroad(pName, cityA, distance, cityB);
		if (cityA == "" || cityB == "" || distance <= 0)
		{
			throw maplineerr;
		}

		if (check.existA == true && check.existB == true)
		{
			switch (check.correctdist)
			{
				case nodist:
					addroad(pName, distance, check);
					//cout << "added" << cityA << " " << cityB << " " << distance << endl;wypisuje co dodano
					break;
				case okdist:
					continue;
					break;
				case wasdiffrentdist:
					throw wasdiffrentdist;
					break;
			}
			
		}
		else
		{
			if (check.existA == false)
			{
				addcity(pName, cityA);
			}
			if (check.existB == false)
			{
				addcity(pName, cityB);
			}

			check = existroad(pName, cityA, distance, cityB);
			addroad(pName, distance, check);
			//cout << "added " << cityA << " " << cityB << " " << distance << endl;
		}
	}
	//cout << "loading complete" << endl;

	return;
}

