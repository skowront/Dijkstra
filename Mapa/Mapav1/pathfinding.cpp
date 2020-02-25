/**@file
*\brief Plik zawiera funkcje kluczowe do wykonania algorytmu Dijkstry i znalezienia o ile istnieje drogi z A do B.
*\author Tomasz Skowron
*\see pathfinding.cpp
*/
#include "Mapheader.h"
#include "Valid.h"  
#include "Service.h"
#include "Cleanse.h"
#include "pathfinding.h"
#include "Loading.h"



pathtab * initialize(lcities *& pName,pathtab *& path)
{
	if (pName)
	{
		auto pHeadN = pName;
		path = new pathtab{ pHeadN,0,nullptr,false,nullptr };
		auto pHeadP = path;
		pHeadN=pHeadN->pNextCity;
		while (pHeadN)
		{
			pHeadP->nextpathtab = new pathtab{ pHeadN,0,nullptr,false,nullptr };
			pHeadP = pHeadP->nextpathtab;
			pHeadN = pHeadN->pNextCity;
		}
		return path;
	}
	return nullptr;
}


pathtab * findinpath(pathtab *& path, const string & cityA)
{
	auto element = path;
	while (element)
	{
		if (element->vertex->city == cityA)
		{
			return element;
		}
		else
		{
			element = element->nextpathtab;
		}
	}
	return nullptr;
}


lcities * findiname(lcities *& pName, const string & cityA)
{
	auto element = pName;
	while (element)
	{
		if (element->city == cityA)
		{
			return element;
		}
		else
		{
			element = element->pNextCity;
		}
	}
	throw noroute;
}


pathtab *findmin(pathtab *& path,const string &cityA)
{
	auto pHeadP = path;
	auto min = path;
	min = nullptr;
	while (pHeadP)
	{
		if (pHeadP->visited == true || pHeadP->vertex->city == cityA)
		{
			pHeadP = pHeadP->nextpathtab;
			continue;
		}
		if (min == nullptr)//dla sytuacji mapy rozdzielnej, dojdzie do zapisania infinity w vertex'ie oddzielnej czesci mapy
		{
			min = pHeadP;
		}
		if (pHeadP->sdist < min->sdist && pHeadP->sdist!=0)
		{
			min = pHeadP;
			pHeadP = pHeadP->nextpathtab;
			continue;
		}
		if (pHeadP->sdist != 0 && min->sdist==0)
		{
			min = pHeadP;
		}
		pHeadP = pHeadP->nextpathtab;
	}
	return min;
}


bool allvisited(pathtab *& path,const string & cityA)
{
	auto pHeadP = path;
	while (pHeadP)
	{
		if (pHeadP->visited == false&&pHeadP->vertex->city!=cityA)
		{
			return false;
		}
		pHeadP = pHeadP->nextpathtab;
	}
	return true;
}


pathtab findshortAB(lcities *& pName,const string & cityA, const string cityB,pathtab *& path)
{
	if (findiname(pName,cityA)->pNextDist == nullptr)
	{
		throw noroute;
	}
	path = initialize(pName, path);
	auto pHeadN = findiname(pName,cityA);
	double knowndist = 0;
	while (true)
	{
			auto pHeadP = path;
			auto pHeadD = pHeadN->pNextDist;
			while (pHeadD)
			{
				if (pHeadD->pNextCity->city == cityA)
				{
					auto temp=findinpath(path,cityA);
					temp->visited = true;
					pHeadD = pHeadD->pNextDist;
					continue;
				}
				else
				{
					
					pHeadP = findinpath(path, pHeadD->pNextCity->city);
					auto incoming = findinpath(path,pHeadN->city);//miasto z ktorego przychodzimy
					
					
					if (pHeadP->sdist > pHeadD->dist+incoming->sdist || pHeadP->sdist == 0)
					{
						auto incoming = findinpath(path, pHeadN->city);
						pHeadP->sdist = pHeadD->dist+incoming->sdist;
						pHeadP->pvertex = pHeadN;
					}
					
				}
				pHeadD = pHeadD->pNextDist;
			}
			pHeadP = findinpath(path, pHeadN->city);
			pHeadP->visited = true;
			
			if (allvisited(path,cityA))
			{
				break;
			}
			if (pHeadP->vertex->city == cityB)
			{
				knowndist = findinpath(path, cityB)->sdist;
				if (findmin(path, cityA)->sdist > knowndist)
				{
					throw earlyhit;
				}
			}
			pHeadP = findmin(path, cityA);
			
			pHeadN = findiname(pName, pHeadP->vertex->city);
	}
	
	return *path;
}


bool existV(ldirect *& pVisited, const string & city)
{
	auto pHeadV = pVisited;
	while(pHeadV)
	{
		if (pHeadV->vertex->vertex->city==city)
		{
			return true;
		}
		pHeadV = pHeadV->lvNext;
	}
	return false;
}


bool existroadAtoB(const string & cityA, const string & cityB, lcities *& pName)
{
	if (pName)
	{
		auto pHeadN = pName;
		while (pHeadN)
		{
			auto pHeadD = pHeadN->pNextDist;
			if (pHeadN->city == cityA)
			{
				while (pHeadD)
				{
					if (pHeadD->pNextCity->city == cityB)
					{
						return true;
					}
					pHeadD = pHeadD->pNextDist;
				}
				return false;
			}
			
			pHeadN = pHeadN->pNextCity;
		}

		return false;
	}
	return false;
}


bool allroadexist(ldirect *& pVisited,lcities *& pName,const string & startcity)
{
	auto pHeadV = pVisited;
	while (pHeadV)
	{
		if (pHeadV->vertex->pvertex->city == startcity)//startcity bedzie na koncu zawsze wiec mozna to tak zostawic
		{
			break;
		}
		if (!existroadAtoB(pHeadV->vertex->pvertex->city, pHeadV->vertex->vertex->city, pName))
		{
			return false;
		}
		pHeadV = pHeadV->lvNext;
	}
	return true;
}


ldirect * interpret(pathtab *&path,const string & cityA, const string & cityB,lcities*& pName)
{
	if (path)
	{
		auto pHeadP = findinpath(path,cityB);
		ldirect * pVisited = nullptr;
		if (pHeadP->sdist == 0||pHeadP->visited==false)
		{
			throw noroute;
		}
		while(true)
		{
			if (pHeadP->vertex->city == cityA)
			{
				if (!pVisited)
				{
					pVisited = new ldirect{findinpath(path,pHeadP->vertex->city),nullptr};
				}
				else
				{
					auto pHeadV = pVisited;
					while (pHeadV->lvNext)
					{
						pHeadV = pHeadV->lvNext;
					}
					pHeadV->lvNext = new ldirect {findinpath(path,pHeadP->vertex->city),nullptr};
				}
				break;
			}
			else
			{
				if (!pVisited)
				{
					pVisited = new ldirect{ findinpath(path,pHeadP->vertex->city),nullptr };
				}
				else
				{
					auto pHeadV = pVisited;
					while (pHeadV->lvNext)
					{
						pHeadV = pHeadV->lvNext;
					}
					pHeadV->lvNext = new ldirect{ findinpath(path,pHeadP->vertex->city),nullptr };
				}
			}
			if (pHeadP->pvertex == nullptr)
			{
				complexclean(pName,0,path,1,pVisited,1);
				throw noroute;
			}
			pHeadP = findinpath(path, pHeadP->pvertex->city);
			if (existV(pVisited, pHeadP->vertex->city))
			{
				complexclean(pName, 0, path, 1, pVisited, 1);
				throw noroute;
			}
		}
		if (!allroadexist(pVisited,pName,cityA))
		{
			complexclean(pName, 0, path, 1, pVisited, 1);
			throw noroute;
		}
		else
		{
			return pVisited;
		}
	}
	else 
	{
		throw noroute;
	}
	return nullptr;
}




ldirect * findinvisited(ldirect*& pVisited, const string & city)
{
	auto pHeadV = pVisited;
	while (pHeadV)
	{
		if (pHeadV->vertex->vertex->city == city)
		{
			return pHeadV;
		}
		pHeadV = pHeadV->lvNext;
	}
	return nullptr;
}

void writeroute(ldirect *& route, ostream & stream)
{
	if (!route->lvNext)
	{
		return;
	}
	if (route->lvNext)
	{
		writeroute(route->lvNext,stream);
	}
	stream << route->vertex->pvertex->city << "--" << route->vertex->sdist << "-->" << route->vertex->vertex->city << endl;
	return;
}


void weightless(ldirect *& route,const string & endcity,const string & startcity)
{
	auto pHeadV = route;
	pHeadV = findinvisited(pHeadV,endcity);
	while (pHeadV&&pHeadV->vertex->vertex->city!=startcity)
	{
		auto temp = findinvisited(route, pHeadV->vertex->pvertex->city);
		pHeadV->vertex->sdist = pHeadV->vertex->sdist-temp->vertex->sdist;
		pHeadV = temp;
	}
}


double getweight(pathtab *& path, const string & city)
{
	double value = 0;
	auto pHeadP = path;
	if (pHeadP) 
	{
		while (pHeadP)
		{
			if (pHeadP->vertex->city == city)
			{
				value = pHeadP->sdist;
				return value;
			}
			pHeadP = pHeadP->nextpathtab;
		}
	}
	else
	{
		return 0;
	}
	return 0;
}
