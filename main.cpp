/*
*	File : main.cpp
*	Author :  Nicholas Robless
*	Date : 4/22/2016
*	Purpose : Main file of Dictionary. Used to read, modify, and output a dictionary file using binary search trees.
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <locale>
#include <functional>

#include "DictionaryDriver.h"

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
		std::cout << "Invalid number of arguments! Please provide a dictionary file name." << '\n';
	}
    else
    {
        DictionaryDriver driver;
        driver.createTree(argv[1]);
        driver.run();
    }

	return 0;
}
