#pragma once
#include <set>
#include <vector>
#include <string>
#include <map>

using namespace std;
struct fileKWStr
{
	wstring use = L"";
	wstring extension = L"";
	wstring size = L"";
	wstring lod = L"";
	wstring variation = L"";
};

class KeywordManager
{
public:
	bool initJsonMap(wstring myIDPath, wstring myKWPath, wstring myDiction, wstring myNameUsagePath);
	set<wstring> dictionary;
	map<wstring, vector<wstring>> idMap;
	map<wstring, vector<wstring>> kWMap;
	map<wstring, wstring> usageNameMap;
	
	static KeywordManager* getInstance();
	bool dictionarySearch(std::wstring);
	void getKeywords(std::wstring , std::vector <std::wstring> & );
	void analyseID(vector < std::wstring > , map <wstring , wstring> &);
	short getObjectID(wstring mySource, std::wstring & myTarget );
	void generateObjectID(wstring , wstring &);
	wstring makeFileName(wstring objectID, wstring sourceFile, fileKWStr  & resultKWStr);
	wstring usageNameConvert(wstring);
	bool makeFileKeyword();
	void exportObjectID();
	short getFileType(wstring);
private:
	vector<wstring> extension2D;
	vector<wstring> extension3D;
	vector<wstring> extensionOther;
	static KeywordManager* instance;
	wstring getfileKWType(wstring , fileKWStr& );
	wstring nameFromFileKWStr(wstring, fileKWStr);
	bool initDictionary(wstring myDictionPath);

	KeywordManager();
	~KeywordManager();
};