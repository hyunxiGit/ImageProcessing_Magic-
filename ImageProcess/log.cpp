#pragma once
#include "stdafx.h"

//todo : This class better use vector
void Log::logFileIn(WCHAR ** myNames, int myCount, int & myRecorded) 
{
//todo : setlocale ony in one place
	std::locale chs("chs");
	wifstream myLog;
	myLog.imbue(chs);

	bool overFlow = false;

	//open file
	myLog.open(LOG_PATH, std::ifstream::in);
	if (!myLog.is_open())
	{
		cout << "faild to open the file" << endl;
		return;
	}
	myRecorded = 0;
	while (!myLog.eof())
	{
		if (myRecorded < myCount)
		{
			myLog >> myNames[myRecorded];
			myRecorded++;
		}
		else
		{
			overFlow = true;
			break;
		}
	}
	myLog.close();

	if (overFlow)
	{
		wcout << "[log :: logFileIn]" << endl;
		wcout << "the name array is too small" << endl;
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