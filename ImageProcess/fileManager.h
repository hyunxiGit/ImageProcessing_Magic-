#pragma once
class fileManager
{
private:
	static fileManager* theFileManager;
	fileManager();
	
	char root;
	//root
	/*root = e:\nicholas_rwc_jx4_data\depot\JX4_SourceData\Graphics\Megascans\surfaces\*/
public:
	static fileManager* getInstance();
	//static void outputUnicode();
	//static void iterateFolder();
	//static void createFolder();
	int test;


	
};
