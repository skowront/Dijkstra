/**@file
*\brief Zawiera funkcje to tworzenia stringow tylko ze znakami dozwolonymi.
*\author Tomasz Skowron
*\see Valid.h
*/
#include "Mapheader.h"
#include "Valid.h"  
#include "Service.h"
#include "Cleanse.h"
#include "pathfinding.h"
#include "Loading.h"



string charonly(const string input)
{
	string tempinputinternal="";
	for (int i = 0; i < input.length(); i++)
	{
		if ('/'<input[i] && input[i]<':'/*[0;9]*/|| '@'<input[i] && input[i]<'['/*[A;Z]*/|| 'a'<=input[i] && input[i]<'{'/*[a; z]*/)
		{
			tempinputinternal = tempinputinternal + input[i];
		}
	}
	return tempinputinternal;

}
