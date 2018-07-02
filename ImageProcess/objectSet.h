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
	bool init(pair<wstring, wstring> myIdPaire, FileManager * myFM, KeywordManager * myKM, TextureSetManager * myTM);
	bool setIDPath(wstring myMegaId, wstring myObjId, wstring mySourcePath, wstring myTargetPath);
	bool generateID();
	wstring getObjectID();
	bool setTst(wstring tst);
	bool makeTextet();
	void reformat2D(wstring myFormat);
	void makeObjectTargetFolder();
	void exportAsset(bool export2D, bool exportTextet, bool export3D = false);
	void export2D();
	wstring getTargetPath();

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