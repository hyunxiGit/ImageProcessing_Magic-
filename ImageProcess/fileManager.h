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


	wstring root;
	//root
	/*root = e:/nicholas_rwc_jx4_data/depot/JX4_SourceData/Graphics/Megascans/surfaces/*/

public:
	static FileManager* getInstance();
	bool    setRoot(wstring);
	wstring getRoot();
	void iterateFolder(std::vector <std::wstring> & , std::vector <std::wstring> &, wstring);
	void createFolder();
	int test;
	
};
