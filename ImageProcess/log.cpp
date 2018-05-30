#pragma once
#include "stdafx.h"

void Log::logFileIn(WCHAR ** myNames, int myCount) 
{
//todo : setlocale ony in one place
	std::locale chs("chs");
	wifstream myLog;
	myLog.imbue(chs);


	//open file
	myLog.open(LOG_PATH, std::ifstream::in);
	if (!myLog.is_open())
	{
		cout << "faild to open the file" << endl;
		return;
	}
	int recorded = 0;
	while (!myLog.eof())
	{
		myLog >> myNames[recorded];
		recorded++;
	}
	myLog.close();

	for (int i = 0; i < recorded; i++)
	{
		wcout << myNames[i] << endl;
	}
}
void Log::logFilesOut(WCHAR ** myNames, int myCount)
{

	//todo : setlocale ony in one place
	std::locale chs("chs");
	wofstream myLog;
	myLog.imbue(chs);
	//open file
	myLog.open(LOG_PATH, ios::app);

	if (myLog.is_open())
	{
		for (int i = 0; i < myCount; i++)
		{
			myLog << myNames[i] << endl;
		}
		myLog.close();
	}
}