#pragma once
#include "keywordManager.h"
#include <vector>
using namespace std;
class ObjectSet
{
public :
	ObjectSet();
	bool init(wstring, wstring, wstring);
	bool generateID();
	wstring getObjectID();
	void generateTextureSet();
	bool setPath(wstring, wstring);
	void exportSet();
	bool analyseObjectSet(vector<wstring>);
private:
	wstring sourcePath;
	wstring targetPath;
	wstring megaScanId;
	wstring objectId;
};