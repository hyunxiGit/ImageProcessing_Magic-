#pragma once
#include "stdafx.h"
#define BUFFER_SIZE 50
//todo this function is purely test for support Unicode it should be somewhere else
void outputUnicode()
{
	//method 1 : 使用wprintf

	char scp[16];
	int cp = GetACP();
	sprintf_s(scp, ".%d", cp);
	setlocale(LC_ALL, scp);
	wprintf(L"测试1234");

	//method 2 : 使用wcout
	/*
	locale loc("chs");
	//locale loc( "Chinese-simplified" );
	//locale loc( "ZHI" );
	//locale loc( ".936" );
	wcout.imbue(loc);
	std::wcout << L"中国" << endl;
	*/
}


void WCS_to_MCS()
{
	//wcstombs_s WCS 向 MCS 做转换的例子
	
	size_t   i;
	//destiny
	char      *pmbbuffer = (char *)malloc(BUFFER_SIZE);

	//source
	const wchar_t* pWCBuffer = L"Hello, world.";

	printf("convert wide-character string:\n");

	// conversion
	wcstombs_s(&i, pmbbuffer, (size_t)BUFFER_SIZE,
	pWCBuffer, (size_t)BUFFER_SIZE);

	// output
	printf("   characters converted: %u\n", i);
	printf("    multibyte character: %s\n\n",
	pmbbuffer);

	// free multibyte character buffer
	if (pmbbuffer)
	{
	free(pmbbuffer);
	}

	
}

//向文件（中文文件名）输出wchar / wide char string
void wchatTestFunction()
{
	setlocale(LC_ALL, "");
	wchar_t wc1[5] = L"我是";
	wprintf(L"wprint test %ls", wc1);
	wprintf(L"size of wc1 : %i", sizeof(wc1));

	int err;

	FILE* myFile;
	err = _wfopen_s(&myFile, L"d:/我的.txt", L"w+");

	if (err == 0)
	{
		printf("The file 'crt_fopen_s.c' was opened\n");
	}
	fwprintf(myFile, wc1);
	fwprintf(myFile, wc1);
	fclose(myFile);

	// 转化wcharstring 为 multi byte string

	size_t oncverted;
	char * mbs = nullptr;
	//分配大小
	mbs = (char *)malloc(BUFFER_SIZE);

	const wchar_t * wc2 = L"来了";
	wcstombs_s(&oncverted, mbs, BUFFER_SIZE, wc2, BUFFER_SIZE);

}

void deleteFolder()
{
	//system("dir \\testtmp");
	//删除文件夹
	/*if (_wrmdir("\\testtmp") == 0)
	printf("Directory '\\testtmp' was successfully removed\n");
	else
	printf("Problem removing directory '\\testtmp'\n");*/
}

void logFileIn(std::vector <std::wstring> & myInVector)
{
	//todo : setlocale ony in one place
	std::locale chs("chs");
	wifstream myLog;
	myLog.imbue(chs);

	bool overFlow = false;

	//open file
	myLog.open(L"d:/test.txt", std::ifstream::in);
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

void logFilesOut(std::vector <std::wstring> & myOutVector)
{
	//todo : setlocale ony in one place
	std::locale chs("chs");
	wofstream myLog;
	myLog.imbue(chs);

	//open file
	myLog.open(L"d:/test.txt", ios::app);

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
