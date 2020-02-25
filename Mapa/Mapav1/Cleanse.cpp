/** @file
*\brief Plik zawiera funkcje do usuwania struktur powstalych w wyniku dzialania programu.
*\author Tomasz Skowron
*\see Cleanse.h
*/
#include "Mapheader.h"
#include "Valid.h"  
#include "Service.h"
#include "Cleanse.h"
#include "pathfinding.h"
#include "Loading.h"


void clean(lcities * & pName)
{
	auto pHeadN = pName;
	auto pN = pHeadN;
	
	if (pName)
	{
		auto pHeadD = pName->pNextDist;
		auto pD = pHeadD;
		while (pHeadN)
		{
			pHeadD = pHeadN->pNextDist;
			while (pHeadD)
			{
				//cout << "deleted:" << pHeadD->dist << endl;
				pD = pHeadD;
				pHeadD = pHeadD->pNextDist;
				delete pD;
				pD = nullptr;
				
			}
			//cout << "deleted:" << pHeadN->city << endl;
			pN = pHeadN;
			pHeadN = pHeadN->pNextCity;
			delete pN;
			pN = nullptr;
		}
		pName = nullptr;
	}
	return;
}


void cleanroute(ldirect *& route)
{
	auto pHeadR = route;
	while (pHeadR)
	{
		route = route->lvNext;
		delete pHeadR;
		pHeadR = route;
	}
	return;
}


void cleanpath(pathtab *& path)
{
	auto pHeadP = path;
	while (path)
	{
		path = path->nextpathtab;
		delete pHeadP;
		pHeadP = path;
	}
	delete path;
	return;
}


void complexclean(lcities *& pName,bool pn,pathtab *&path,bool pt, ldirect * &route,bool rt)
{
	if (route&&rt)
	{
		cleanroute(route);
		cleanroute(route);
	}
	if (path&&pt)
	{
		cleanpath(path);
		cleanpath(path);
	}
	if (pName&&pn)
	{
		clean(pName);
		clean(pName);
	}
	return;
}
