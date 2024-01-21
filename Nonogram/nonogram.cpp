/**
*
* Solution to course project # 9
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2023/2024
*
* @author Ivana Dimitrova
* @idnumber 7MI0600376
* @compiler Visual Studio
*
* <the nonogram game>
*
*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>

#include "function.h"

int main() 
{
	char yesOrNo = '0';
	entrance(yesOrNo);

	chooseRandomFile("Level 1.1.txt", "Level 1.2.txt");

	return 0;
}

