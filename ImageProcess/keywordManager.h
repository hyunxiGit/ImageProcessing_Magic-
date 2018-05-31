#pragma once
#include <set>
#include <vector>
#include <string>
#include <map>
class KeywordManager
{
public:
	std::set<std::wstring> dictionary;
	std::map<std::wstring, short> idMap;
	
	static KeywordManager* getInstance();

	bool dictionarySearch(std::wstring);
	void getKeywords(std::wstring , std::vector <std::wstring> &);
	bool generateObjectID(std::wstring mySource, std::wstring & myTarget);

	short addId(std::wstring);

private:
	char dictionaryPath[MAX_PATH];
	char iDPath[MAX_PATH];

	static KeywordManager* instance;
	

	KeywordManager();
	~KeywordManager();
};