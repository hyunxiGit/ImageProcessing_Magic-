#pragma once
#include <vector>
#include <string>
#include "keywordManager.h";
#include "log.h";

#define ILLEGAL_PATH -1
#define FOLDER_EXIST 2
#define FILE_EXIST 1

//fileManager 的 singleton 用法:
//FileManager*  myFileManager = FileManager::getInstance();
using namespace std;
class FileManager
{
private:
	static FileManager* instance;
	FileManager();


	wstring batchInputPath;
	wstring batchOutputPath;
	wstring toolFileStorePath;
	wstring IDJsonPath;
	wstring keyWordJsonPath;
	wstring dictionJsonPath;
	wstring logPath;

public:
	static FileManager* getInstance();
	static short checkPath(wstring);
	short initDirectory(wstring mySource, wstring myTarget, wstring myToolStoragePath);
	short initFile();
	bool setToolFileStoragePath(wstring);
	bool setBatchInputPath(wstring);
	bool setBatchExportPath(wstring);
	bool createFile(wstring);
	wstring getToolFileStoragePath();
	wstring getBatchInputPath();
	wstring getBatchOutputPath();
	wstring getIDJasonPath();
	wstring getKeywordJsonPath();
	wstring getDictionTxtPath();
	void iterateFolder(vector <std::wstring> & , std::vector <std::wstring> &, wstring, bool mySubFolder = false);
	short createFolder(wstring);
	wstring getFileExtion(wstring);
};
