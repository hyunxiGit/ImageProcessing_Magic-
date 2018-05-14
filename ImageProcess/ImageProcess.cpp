// ImageProcess.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>

void stringSearch();

int main()
{
	stringSearch();
	std::getchar();
    return 0;
}

void jsonIO()
{

}

void stringSearch()
{
	string search = "humidity";
	string line;
	ifstream inFile;
	bool found = false;
	unsigned int curLine = 0;

	inFile.open("d:/en-dictionary.txt");
	if (!inFile)
	{
		cout << "unable to open file" << endl;
	}
	else
	{
		while (getline(inFile, line))
		{
			curLine++;
			if (line.find(search) != string::npos)
			{
				cout << "found" << endl;
				found = true;
				break;
			}
		}
		cout << found << endl;
	}
}

void convertImage()
{
	Image myImg("oebei_4K_Albedo.jpg");
	myImg.write("oebei_4K_Albedo.tga");
}

