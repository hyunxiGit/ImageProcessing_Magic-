// ImageProcess.cpp : Defines the entry point for the console application.
//
#pragma once
#include "stdafx.h"
void convertImage();

int main()
{
	//fileManager 的 singleton 
	FileManager*  myFileManager = FileManager::getInstance();
	cout << myFileManager->test << endl;

	system("pause");
	return 0;
}