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
	set<std::wstring> dictionary;
	map<std::wstring, short> idMap;
	map<wstring, vector<wstring>> fileKWMap;
	
	static KeywordManager* getInstance();
	bool dictionarySearch(std::wstring);
	void getKeywords(std::wstring , std::vector <std::wstring> & );
	short getObjectID(map<wstring, vector<wstring>> & , wstring mySource, std::wstring & myTarget );
	void generateObjectID(map<wstring, vector<wstring>> & , wstring , wstring &);
	wstring getFileName(wstring , wstring , fileKWStr &);
	bool makeFileKeyword();
private:
	char dictionaryPath[MAX_PATH];
	char iDPath[MAX_PATH];

	static KeywordManager* instance;
	wstring getfileKWType(wstring , fileKWStr& );

	wstring makeFileName(wstring, fileKWStr);

	KeywordManager();
	~KeywordManager();
};