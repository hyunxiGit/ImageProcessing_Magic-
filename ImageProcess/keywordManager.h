#pragma once
#include <set>
#include <vector>
#include <string>
class KeywordManager
{
private:
	static KeywordManager* instance;
	KeywordManager();
	std::set<std::wstring> myDictionary;
	char dictionaryPath [MAX_PATH];
public:
	static KeywordManager* getInstance();
	bool dictionarySearch(std::wstring);
	void getKeywords(std::wstring , std::vector <std::wstring> &);
	void generateObjectID (std::wstring mySource, std::wstring & myTarget);

};