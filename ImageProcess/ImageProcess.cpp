// ImageProcess.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


#pragma comment(lib, "User32.lib")

void dictionarySearch();
void fileManagement_iterateFolder();
void convertImage();
void fileManagement_outputUnicode();

int main()
{
	//dictionarySearch();
	//	//for testing not closing the console
	//	std::getchar();
	fileManagement_iterateFolder();

	//fileManagement_outputUnicode();

	getchar();
	return 0;
}

void jsonIO()
{

}

void fileManagement_outputUnicode()
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
 
void fileManagement_iterateFolder()
{
	//输出 unicode
	//这段代码保证Unicode的输出啊
	char scp[16];
	int cp = GetACP();
	sprintf_s(scp, ".%d", cp);
	setlocale(LC_ALL, scp);
	//wprintf(L"测试1234");

	//输出 Unicode 啊

	//iterate folder part
	HANDLE hFind = INVALID_HANDLE_VALUE;
	TCHAR szDir[MAX_PATH];
	WIN32_FIND_DATA ffd;
	DWORD dwError = 0;

	StringCchCopy(szDir, MAX_PATH, L"d:/");
	hFind = FindFirstFile(szDir, &ffd);
	//hFind = FindFirstFile(L"d:\\*.*", &ffd);
	hFind = FindFirstFile(L"d:\\我的.txt", &ffd);

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
			/*cout << ffd.cFileName;
			cout << " ";
			cout << "<DIR>" << endl;*/
			_tprintf(TEXT("  %s   <DIR>\n"), ffd.cFileName);
		}
		else
		{
			//cout << ffd.cFileName <<endl;
			_tprintf(TEXT("  %s   \n"), ffd.cFileName);
		}
	} while (FindNextFile(hFind, &ffd) != 0);

}

void fileManagement_createFolder()
{
	//support Unicode
	//CreateDirectory part

	TCHAR szDirName[] = L"D:\\我test";
	bool flag = CreateDirectory(szDirName, NULL);
	DWORD ERROR_File_Exist = 183;
	DWORD err = GetLastError();
	if (err == ERROR_File_Exist)
	{
		cout << "the file already exist" << endl;
	}
	cout << "flag: " << flag << endl;
	cout << "err: " << err << endl;
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
	Image myImg("d:\\oebei_4K_Albedo.jpg");
	myImg.write("d:/oebei_4K_Albedo.tga");
}

