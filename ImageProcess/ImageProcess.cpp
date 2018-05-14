// ImageProcess.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


#pragma comment(lib, "User32.lib")

void dictionarySearch();
void fileManagement();
void convertImage();

int main()
{
	//dictionarySearch();
	//	//for testing not closing the console
	//	std::getchar();
	getchar();
	return 0;
}

void jsonIO()
{

}

void fileManagement()
{
	HANDLE hFind = INVALID_HANDLE_VALUE;
	TCHAR szDir[MAX_PATH];
	WIN32_FIND_DATA ffd;
	DWORD dwError = 0;

	StringCchCopy(szDir, MAX_PATH, L"d:/");
	hFind = FindFirstFile(szDir, &ffd);
	hFind = FindFirstFile(L"d:\\*.*", &ffd);

	if (INVALID_HANDLE_VALUE == hFind)
	{
		//DisplayErrorBox(TEXT("FindFirstFile"));
		cout << "incorrect" << endl;
	}
	do
	{
		cout << "find" << endl;
		if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			_tprintf(TEXT("  %s   <DIR>\n"), ffd.cFileName);
		}
		else
		{
			_tprintf(TEXT("  %s   %ld bytes\n"), ffd.cFileName);
		}
	} while (FindNextFile(hFind, &ffd) != 0);

}

//	stringSearch();
void dictionarySearch()
{
	//dictionary feature test
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

