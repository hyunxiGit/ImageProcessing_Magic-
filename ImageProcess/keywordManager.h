#pragma once
#include <set>
#include <vector>
#include <string>
#include <map>
using namespace std;
class KeywordManager
{
public:
	std::set<std::wstring> dictionary;
	std::map<std::wstring, short> idMap;
	
	static KeywordManager* getInstance();
	bool dictionarySearch(std::wstring);
	void getKeywords(std::wstring , std::vector <std::wstring> & );
	short getObjectID(map<wstring, vector<wstring>> & , wstring mySource, std::wstring & myTarget );
	void generateObjectID(map<wstring, vector<wstring>> & , wstring , wstring &);
	wstring getFileName(wstring , wstring);
private:
	char dictionaryPath[MAX_PATH];
	char iDPath[MAX_PATH];

	static KeywordManager* instance;
	

	KeywordManager();
	~KeywordManager();
};