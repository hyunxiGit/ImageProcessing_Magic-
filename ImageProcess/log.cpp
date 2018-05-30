#pragma once
#include "stdafx.h"

//todo : This class better use vector

void Log::logFileIn(std::vector <std::wstring> & myInVector)
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

	std::wstring myInString;
	while (!myLog.eof())
	{
		myLog >> myInString;
		myInVector.push_back(myInString);	
	}
	myLog.close();
	
}

void Log::logFilesOut(std::vector <std::wstring> & myOutVector)
{
	//todo : setlocale ony in one place
	std::locale chs("chs");
	wofstream myLog;
	myLog.imbue(chs);

	//open file
	myLog.open(LOG_PATH, ios::app);

	if (myLog.is_open())
	{
		std::vector<std::wstring>::iterator it;
		for (it = myOutVector.begin(); it != myOutVector.end(); it++)
		{
			myLog << *it << endl;
		}
		myLog.close();
	}
}
