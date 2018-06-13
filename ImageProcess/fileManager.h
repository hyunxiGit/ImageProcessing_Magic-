#pragma once
#include <vector>
#include <string>

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

public:
	static FileManager* getInstance();
	bool checkPath(wstring);
	short init(wstring mySource, wstring myTarget);
	bool setToolFileStoragePath(wstring);
	bool setBatchInputPath(wstring);
	bool setBatchExportPath(wstring);
	wstring getBatchInputPath();
	wstring getBatchOutputPath();
	void iterateFolder(vector <std::wstring> & , std::vector <std::wstring> &, wstring);
	short createFolder(wstring);
	
};
