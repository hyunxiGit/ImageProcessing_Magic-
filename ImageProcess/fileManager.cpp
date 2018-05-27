#pragma once
#include "stdafx.h"
#define BUFFER_SIZE 50

//empty pointer assignment
void logFileOut(TCHAR *);
FileManager* FileManager::instance = nullptr;

FileManager::FileManager()
{
	//todo : 不使用常量使用传入值
	//公司环境
	//LPCWSTR myroot = L"e:/nicholas_rwc_jx4_data/depot/JX4_SourceData/Graphics/Megascans/surfaces/";	
	//家里环境
	LPCWSTR myroot = L"F:/我的/surfaces/";
	setRoot(myroot);
}

FileManager* FileManager:: getInstance()
{
	FileManager* result;
	if (instance == nullptr)
	{
		instance = new FileManager();
	}
	result = instance;
	return(instance);
}

bool FileManager::setRoot(LPCWSTR myPath)
{
	StringCchCopy(root, MAX_PATH, myPath);
	cout << "current root is : ";
	locale loc("chs");
	wcout.imbue(loc);
	std::wcout << root << endl;
	return (true);
}
void FileManager::iterateFolder()
{

	HANDLE hFind = INVALID_HANDLE_VALUE;
	TCHAR szDir[MAX_PATH];
	WIN32_FIND_DATA ffd;
	DWORD dwError = 0;

	//set root
	StringCchCopy(szDir, MAX_PATH, root);

	//set search path
	StringCchCat(szDir, MAX_PATH, L"*.*");
	hFind = FindFirstFile(szDir, &ffd);

	if (INVALID_HANDLE_VALUE == hFind)
	{
		cout << "path can not be found" << endl;
	}
	do
	{
		if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			// These 2 folder should be ignore
			if (lstrcmpW(ffd.cFileName, L".") == 0) {}
			if (lstrcmpW(ffd.cFileName, L"..") == 0) {}
			std :: wcout << ffd.cFileName << " <DIR> " << endl;
		}
		else
		{
			//cout << ffd.cFileName <<endl;
			_tprintf(TEXT("  %s   \n"), ffd.cFileName);
		}
		logFileOut(ffd.cFileName);
	} while (FindNextFile(hFind, &ffd) != 0);
	
}

void logFileOut(TCHAR * szDir)
{
	char path[] = "d:/test.txt" ;
	std::locale chs("chs");
	wofstream myLog;
	myLog.imbue(chs);

	myLog.open(path, ios::app);

	if (myLog.is_open())
	{
		myLog << szDir<<endl;
		myLog.close();
	}
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
	//找所有 文件夹
	//hFind = FindFirstFile(L"d:\\*.*", &ffd);
	//找特定的文件
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

//void fileManagement_createFolder()
//{
//	//support Unicode
//	//CreateDirectory part
//
//	TCHAR szDirName[] = L"D:\\我test";
//	bool flag = CreateDirectory(szDirName, NULL);
//	DWORD ERROR_File_Exist = 183;
//	DWORD err = GetLastError();
//	if (err == ERROR_File_Exist)
//	{
//		cout << "the file already exist" << endl;
//	}
//	cout << "flag: " << flag << endl;
//	cout << "err: " << err << endl;
//}



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
	/*
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

	*/
}

void coutFiles()
{
	ofstream myFile;
	const wchar_t *myWC1 = L"测试文件";
	myFile.open("d:/我的.txt");
	myFile << "真的吗" << endl;

}



//字符串的函数测试
void wchatTestFunction()
{
	//向文件（中文文件名）输出wchar / wide char string
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
	fclose(myFile);

	// 转化wcharstring 为 multi byte string

	size_t oncverted;
	char * mbs = nullptr;
	//分配大小
	mbs = (char *)malloc(BUFFER_SIZE);

	const wchar_t * wc2 = L"来了";
	wcstombs_s(&oncverted, mbs, BUFFER_SIZE, wc2, BUFFER_SIZE);



}