// ImageProcess.cpp : Defines the entry point for the console application.
//
#pragma once
#include "stdafx.h"
#include "tst.h"
#include <wchar.h>  
//json temp , should be removed
#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"
#include "rapidjson/filewritestream.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/writer.h"

#include <stdio.h> //json file读

#include "Asset2D.h"
#include "image_w.h"

using namespace std;

bool init();
void testFunction();
void getFolderObjectID();
static FileManager * myFM;
static KeywordManager * myKM;
static Log * myLog;
int main()
{
	bool initSucess = init();
	if (initSucess)
	{
		testFunction();
		//getFolderObjectID();
	}
	Log::exportLog();
	return 0;
}

bool init()
{
	short result;

	myKM = KeywordManager::getInstance();
	myFM = FileManager::getInstance();
	myLog = Log::getInstance();

	locale loc("chs");
	wcout.imbue(loc);

	result = myFM->initDirectory(OFFICE_SOURCE_FOLDER_3D, OFFICE_TARGET_FOLDER, OFFICE_TOOL_FOLDER);
	return(result != -1);
}

void testFunction()
{
	wstring _path = L"E:/nicholas_rwc_jx4_data/sword3-code_S/trunk/sword3-products/trunk/EditorTool/QTextureEditor/Config/TextureSetType/MetalRough01.tst";
	Tst _tst = Tst();
	Serialize::importTst(_path , _tst);
	wcout << "source" << endl;
	for (vector<TstSource>::iterator itr = _tst.sourceNodes.begin(); itr != _tst.sourceNodes.end(); itr++)
	{
		wcout << "...................." << endl;
		wcout << ((TstSource)(*itr)).name<< endl;
		wcout << ((TstSource)(*itr)).colorSpace<< endl;
		wcout << ((TstSource)(*itr)).format << endl;
		wcout << ((TstSource)(*itr)).destID<< endl;
		wcout << ((TstSource)(*itr)).destChannerl<< endl;

	}
	wcout << "dest" << endl;
	for (vector<TstDest>::iterator itr = _tst.destNodes.begin(); itr != _tst.destNodes.end(); itr++)
	{
		wcout << "...................." << endl;
		wcout << ((TstDest)(*itr)).ID << endl;
		wcout << ((TstDest)(*itr)).NameSuffix << endl;
		wcout << ((TstDest)(*itr)).Format << endl;
		wcout << ((TstDest)(*itr)).FileType << endl;
		wcout << ((TstDest)(*itr)).ColorSpace << endl;
		wcout << ((TstDest)(*itr)).Filter << endl;
		wcout << ((TstDest)(*itr)).GenarateMipmap << endl;
		wcout << ((TstDest)(*itr)).MipmapFilter << endl;
		wcout << ((TstDest)(*itr)).Scale << endl;
	}
}

void getFolderObjectID()
//batch process one image folder
{
	//result vectors
	std::vector < std::wstring > myResultFolders;
	std::vector < std::wstring > myResultFiles;

	myFM->iterateFolder(myResultFiles, myResultFolders, myFM->getBatchInputPath());
	
	//analyse targetPath ID and generate json File
	std::vector < std::wstring > myObjectID;
	myKM->analyseID(myResultFolders, myObjectID);
	
	//generate objectSet for each Folder
	vector<ObjectSet> objectsSetVector;
	for (std::vector < std::wstring >::iterator it = myResultFolders.begin(); it != myResultFolders.end(); it++)
	{
		ObjectSet _objSet;
		if (_objSet.init(*it, myFM->getBatchInputPath(), myFM->getBatchOutputPath()))
		{
			objectsSetVector.push_back(_objSet);
		}
	}

	//--------------------------------------------change---------------------------------------------

	//for (std::vector < std::wstring >::iterator it = myResultFolders.begin(); it != myResultFolders.end(); it++)
	//{

		////object folder
		//wstring _folderRoot = myFM->getBatchInputPath() + *it+L"/";
		//std::vector < std::wstring > _subFolders;
		//std::vector < std::wstring > _files;
		////迭代所有的图片文件
		//myFM->iterateFolder(_files, _subFolders, _folderRoot);
		//for (std::vector < std::wstring >::iterator it2 = _files.begin(); it2 != _files.end(); it2++)
		//{
		//	//generate files ID
		//	fileKWStr myKWStr;
		//	wstring _fileName = myKM->getFileName(_objectID, *it2 , myKWStr);

		//	//建立对应的2D asset
		//	if (myKWStr.extension != L".json")
		//	{
		//		Asset2D my2DAsset(_folderRoot, *it2, _newfolderPath, _fileName, myKWStr);
		//		
		//		if (myKWStr.use != L"")
		//		{
		//			
		//			//转存图片
		//			my2DAsset.reformat(L".tga");
		//			my2DAsset.exportAsset();
		//			
		//		}
		//	}

		//}

		
	//}

}
