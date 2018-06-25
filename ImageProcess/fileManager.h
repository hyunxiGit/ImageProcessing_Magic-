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
	void paseInitFile(vector<wstring>);
	
	


	wstring configPath;//config folder
	wstring IDJsonPath;
	wstring keyWordJsonPath;
	wstring dictionJsonPath;
	wstring logPath;
	

	wstring initDir;//initFile directory
	wstring targetDir;//converted megascane folder
	wstring sourceDir;//megascane folder
	wstring tstPath;

	wstring batchInputPath;
	wstring batchOutputPath;

public:
	static FileManager* getInstance();
	static short checkPath(wstring);
	short initDirectory(wstring folderName);
	short initFile();
	bool setToolConfigPath();
	bool setBatchInputPath(wstring);
	bool setBatchExportPath(wstring);
	bool createFile(wstring);
	bool readIni();
	wstring getToolFileStoragePath();
	wstring getBatchInputPath();
	wstring getBatchOutputPath();
	wstring getIDJasonPath();
	wstring getKeywordJsonPath();
	wstring getDictionTxtPath();
	void iterateFolder(vector <std::wstring> & files, std::vector <std::wstring> & folders, wstring targetFolder, bool mySubFolder = false);
	short createFolder(wstring);
	wstring getFileExtion(wstring);
};
