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
	void iterateFolder();
	void createFolder();
	int test;


	
};
