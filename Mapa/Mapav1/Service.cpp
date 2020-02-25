/** @file
*\brief Zawiera funkcje dla main(), do obslugi wprowadzanych danych, czy to w postaci argumentow linii polecen, czy danych bezposrednio z pliku.
*\author Tomasz Skowron
\see Service.h
*/
#include "Mapheader.h"
#include "Valid.h"  
#include "Service.h"
#include "Cleanse.h"
#include "pathfinding.h"
#include "Loading.h"

void printhelp()
{
	cout << "Pomoc dla programu Mapa" << endl;
	cout << "Program przyjmuje parametry:" << endl;
	cout << "-d mapa" << endl;
	cout << "-t trasy do wyszukania" << endl;
	cout << "-o plik wyjsciowy" << endl;
	cout << "Po parametrach nalezy podac sciezke do pliku tekstowego (.txt). Mozna nie podac -t i/lub -o, wtedy program czyta ze standardowego wyjscia" << endl;
	cout << "Wymagany format linii pliku wejsciowgo z mapa: [miasto A] [miasto B] [dystans] np: <A B 10> "<< endl;
	cout << "Wymagany format linii pliku wejsciowgo z trasami: [miasto A] [miasto B] np: <A B > "<< endl;
	cout << "Program akceptuje tylko jedna trase z miasta A do B, ale moze istniec jednoczesnie trasa z A do B i z B do A" << endl;
	cout << "Autor: Tomasz Skowron Informatyka Sem1 2017/2018" << endl;
	return;
}

bool correctparams(const string &ifpath, const string &ofpath, const string & rfpath)
{
	if (ifpath == "")
	{
		throw nominusd;
	}
	if (ofpath == ""&&rfpath=="")
	{
		throw noTnoO;
	}
	if (ofpath == "")
	{
		throw nominuso;
	}
	if (rfpath == "")
	{
		throw nominust;
	}
	return true;
}

void doparameters(int paramixmax, char*params[], string &mfpath, string &ofpath,string & rfpath,bool & wasrf, bool & wasof)
{
	if (paramixmax == 0)
	{
		printhelp();
	}
	else
	{
		for (int i = 0; i < paramixmax; i++)
		{
			string tempparam = params[i];
			if (paramixmax-1 == i)
			{
				break;
			}
			if (tempparam == "-h" || tempparam == "--h")
			{
				printhelp();
			}
			if (tempparam == "-d" || tempparam == "--d")
			{
				mfpath = params[i + 1];
			}
			if (tempparam == "-o" || tempparam == "--o")
			{
				ofpath = params[i + 1];
				wasof = true;
			}
			if (tempparam == "-t" || tempparam == "--t")
			{
				rfpath = params[i + 1];
				wasrf = true;
			}
		}
	}
	correctparams(mfpath,ofpath,rfpath);
	return;
}

void noroad(ostream & outfile, const string & cityA, const string cityB)
{
	outfile << "------------------" << endl;
	outfile << "Trasa z: "<<cityA<<" do "<<cityB <<" --nie mozliwa do wyznaczenia"<< endl;
	outfile << "------------------" << endl;
	return;
}

void core(lcities *& pName, pathtab *& path, ldirect *& route ,ostream & outfile, istream & rfile)
{
		string line;
		string cityA = "";
		string cityB = "";
		const int whatever = 5;
		while (getline(rfile, line))
		{
			complexclean(pName, 0, path, 1, route, 1);
			stringstream ss(line);
			string trash;
			ss >> cityA;
			ss >> cityB;
			ss >> trash;
			if (trash != ""||cityA==""||cityB=="")
			{
				//cout << "bledne dane" << endl;
				continue;
			}
			cityA = charonly(cityA);
			cityB = charonly(cityB);
			existindex check = existroad(pName, cityA, whatever, cityB);
			if (check.existA == false || check.existB == false)
			{
				outfile << cityA << " lub " << cityB << " nie istnieje" << endl;
				continue;
			}
			else
			{
				try
				{
					findshortAB(pName, cityA, cityB, path);
				}
				catch (errorid excep)
				{
					if (excep != earlyhit)
					{
						if (excep == noroute)
						{
							noroad(outfile, cityA, cityB);
							continue;
						}
						throw excep;
					}
				}
				try
				{
					route = interpret(path, cityA, cityB, pName);
				}
				catch (errorid excep)
				{
					complexclean(pName, 0, path, 1, route, 1);
					if (excep == noroute)
					{	
						noroad(outfile, cityA, cityB);
						continue;
					}
					else
					{
						throw excep; 
					}
				}
				outfile << "-----------" << endl;
				double atob = getweight(path, cityB);
				weightless(route, cityB, cityA);
				outfile << atob << " jednostek z " << cityA << " do " << cityB << ":" << endl;
				writeroute(route, outfile);
				outfile << "-----------" << endl;
			}
		}
		return;
}

string allexcep(errorid excep)
{
	switch (excep)
	{
	default:
		return "nieznany  blad \n";
	case maperr:
		return "blad pliku wejsciowego z mapa \n";
	case wasdiffrentdist:
		return "inny dystans miedzy miastami zostal juz podany \n";
	case noroute:
		return "droga nie istnieje \n";
	case earlyhit:
		return "znaleziono trase";
	case maplineerr:
		return "blad w linii w pliku z polaczeniami miedzy miastami \n";
	case nominusd:
		return "nie podano pliku z drogami \n";
	case nominust:
		return "nie podano pliku z trasami do wyznaczenia \n";
	case nominuso:
		return "nie podano pliku wyjsciowego \n";
	case outferr:
		return "blad pliku wyjsciowego \n";
	case routeferr:
		return "blad pliku z drogami do wyznaczenia \n";
	case noTnoO:
		return "nie podano pliku z trasami, ani wyjsciowego \n";
	case donothing:
		break;
	}
	return "";
}

string mainexception(errorid excep, bool & wasrf, bool & wasof)
{
	switch (excep)
	{
	default:
		throw excep;
	case noTnoO:  
		wasrf = false;
		wasof = false;
		return "nie podano pliku z trasami ani wyjsciowego \n";
	case nominust:
		wasrf = false;
		return "nie podano pliku z trasami do wyznaczenia \n";
	case nominuso:
		wasof = false;
		return "nie podano pliku wyjsciowego \n";
	}
}
