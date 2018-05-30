#pragma once
#include <vector>
#include <string>

//fileManager 的 singleton 用法:
//FileManager*  myFileManager = FileManager::getInstance();

class FileManager
{
private:
	static FileManager* instance;
	FileManager();


	TCHAR root[MAX_PATH];
	//root
	/*root = e:/nicholas_rwc_jx4_data/depot/JX4_SourceData/Graphics/Megascans/surfaces/*/

public:
	static FileManager* getInstance();
	bool setRoot(LPCWSTR);
	void iterateFolder(std::vector <std::wstring>);
	void createFolder();
	int test;
	
};
