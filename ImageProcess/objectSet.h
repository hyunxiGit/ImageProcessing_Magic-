#pragma once
#include "keywordManager.h"
#include "asset2D.h"
#include "asset3D.h"
#include "textureSetManager.h"
#include "textet.h"
#include <vector>
using namespace std;
class ObjectSet
{
public :
	ObjectSet();
	bool init(wstring, wstring, wstring);
	bool generateID();
	bool setTst(wstring tst);
	wstring getObjectID();
	bool setPath(wstring, wstring);
	void reformat2D(wstring myFormat);
	void export2D();
	void makeObjectTargetFolder();
	bool makeTextet();
	void exportAsset(bool export2D, bool exportTextet , bool export3D = false);
	
private:
	FileManager * _FM;
	KeywordManager * _KM;
	TextureSetManager * _TM;
	wstring tstName;
	Tst tst;
	vector <Asset2D> asset2;
	vector <Asset3D> asset3;
	Textet textet;
	void generateAsset();
	wstring sourcePath;//object Folder
	wstring targetPath;//object folder
	wstring megaScanId;
	wstring objectId;
};