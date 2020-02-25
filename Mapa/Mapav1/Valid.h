
/**@file 
*\brief Zawiera funkcje to tworzenia stringow tylko ze znakami dozwolonymi.
*\author Tomasz Skowron
*\see Valid.cpp
*/
#ifndef Valid_H
#define Valid_H 

#include "Mapheader.h"
#include <string>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

/**\brief funkcja tworzy nowy string na podstawie podanego, ale tylko z dopuszczalnych znakow, tzn [0-9a-zA-Z]
*@param input - lancuch do przetworzeina
*@return tempinputinternal - nowo utworzony string
*/
string charonly(const string input);

#endif
