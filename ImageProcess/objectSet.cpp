#pragma once
#include "stdafx.h"
#include "objectSet.h"
#include "TextureSetManager.h"
//#include "asset3D.h"

using namespace std;

ObjectSet::ObjectSet() :megaScanId(L""), objectId(L""), sourcePath(L""), targetPath(L"")
{}

bool ObjectSet::init(pair<wstring, wstring> myIdPair, FileManager * myFM, KeywordManager * myKM, TextureSetManager * myTM /*wstring mySourcePath, wstring myTargetPath*/)
//init 函数里面只能使用内存操作，不能使用磁盘操作
//设置路径.产生新ID,产生内存中的assets
{
	_FM = myFM;
	_KM = myKM;
	_TM = myTM;

	bool result = false;
	bool pathSet = setIDPath(myIdPair.first , myIdPair.second, _FM->getBatchInputPath(), _FM->getBatchOutputPath());

	if (!pathSet)
	{
		Log::log(L"<error> < ObjectSet::init> <wrong path> : " + pathSet);
	}
	else
	{
		generateAsset();
		if (asset2.size() > 0 || asset3.size() > 0)
		{
			result = true;
		}
	}
	return(result);
}

bool ObjectSet::generateID() 
{
	bool result = false;
	short getID = _KM->getObjectID(megaScanId, objectId);
	if (getID == 1 || getID == 2)
	{
		result = true;
	}
	return(result);
}

wstring ObjectSet::getObjectID()
{
	return(objectId);
}

bool ObjectSet::setIDPath(wstring myMegaId, wstring myObjId , wstring mySourcePath, wstring myTargetPath)
{
	bool sourceSet = false;
	bool targetSet = false;
	megaScanId = myMegaId;
	if(FileManager::checkPath(mySourcePath) == FOLDER_EXIST)
	{
		sourcePath = mySourcePath;
		sourceSet = true;
		//wcout << sourcePath << endl;
	}
	if (FileManager::checkPath(myTargetPath) == FOLDER_EXIST && myObjId !=L"")
	{
		objectId = myObjId;
		targetPath = myTargetPath + L"/"+objectId;
		targetSet = true;
	}
	else if (_FM->createFolder(myTargetPath) == 1)
	{
		//create a new folder
		targetPath = myTargetPath + L"/" + objectId;
		targetSet = true;
	}
	return(sourceSet && targetSet);
}

void ObjectSet::generateAsset()
{
	vector < wstring > _files;
	vector < wstring > _folder;
	wstring _sourceDir = sourcePath + L"/" + megaScanId+L"/";
	wstring _newFolder = targetPath + L"/"/* + objectId*/;
	_FM->iterateFolder(_files, _folder, _sourceDir, true);
	short assetType = 0;
	for (vector < wstring >::iterator itr = _files.begin(); itr != _files.end(); itr++)
	{
		assetType = _KM->getFileType(*itr);
		fileKWStr myKWStr;
		wstring _fileName = _KM->makeFileName(objectId, *itr, myKWStr);
		
		if (assetType == 2)
		{
			//create 2D asset 
			if (myKWStr.extension == L".jpg")
			{
				//只处理jpg文件
				Asset2D my2DAsset(sourcePath + L"/" + megaScanId, *itr, targetPath, _fileName, myKWStr);
				asset2.push_back (my2DAsset);
			}
			
		}
		else if (assetType == 3)
		{
			//todo : create 3D asset 
			Asset3D my3DAsset(sourcePath + L"/" + megaScanId, *itr, targetPath, _fileName, myKWStr);
			asset3.push_back(my3DAsset);
		}
	}
}

void ObjectSet::makeObjectTargetFolder() 
{
	_FM->createFolder(targetPath);
}

bool ObjectSet::setTst(wstring myTst)
{
	bool result = false;
	if (_TM->checkTstByName(myTst) && asset2.size()>0)
	{
		tstName = myTst;
		tst = _TM->getTstByName(tstName);
		result = true;
	}

	return(result);
}

bool ObjectSet::makeTextet()
{
	bool result = false;
	if (asset2.size()>0)
	{
		vector <Asset2D> assetForTextet;
		for (vector<Asset2D>::iterator itr = asset2.begin(); itr != asset2.end(); itr++)
		{
			wstring _use = (*itr).getStruct().use;
			if (_use == L"preview")
			{
				continue;
			}

			//对属于textet的图片名字进行加工
			//未对应的image 换stru
			wstring textetImgName = _KM->usageNameConvert(_use);
			
			//换成tga格式
			(*itr).reformat(L".tga");

			//wcout << (*itr).getSourceName() << endl;
			if (textetImgName != L"")
			//这是textureet img 文件
			{
				//未对应的image 换name
				(*itr).renameByKW((*itr).getStruct().use, textetImgName);
				//添加对应的textet名字
				(*itr).setTextetImgName(textetImgName);
				//把这些图的地址按tst source node id 顺序打包入数组
				assetForTextet.push_back(*itr);
			}
			else
			{
			}
		}
		
		if (assetForTextet.size() > 0)
		{
			textet =_TM->makeTextset(objectId, assetForTextet, tstName);
			result = true;
		}
	}
	return(result);
}

void ObjectSet::exportTextet(wstring myExportPath)
{
	wstring textetExportDir;
	if (myExportPath != L"")
	{
		wcout << sourcePath + L"/" + megaScanId + L"/" << endl;
		textetExportDir = myExportPath + L"/" + megaScanId + L".texset";
	}
	else
	{
		textetExportDir = targetPath + L"/" + objectId + L".texset";
	}

	wcout << textetExportDir << endl;
	Serialize::exportTextet(textetExportDir, textet);
}

void ObjectSet::reformat2D(wstring myFormat/*L".tga"*/)
{
	for (vector<Asset2D>::iterator itr = asset2.begin(); itr != asset2.end(); itr++)
	{
		(*itr).reformat(myFormat);
	}
}

void ObjectSet::export2D( wstring myFormat) 
{
	//create file test
	for (vector<Asset2D>::iterator itr = asset2.begin(); itr != asset2.end(); itr++)
	{
		//wcout << "new extension is :" << (*itr).getStruct().extension << endl;
		if (myFormat != L"")
		{
			(*itr).reformat(myFormat);
			(*itr).createFile();
			(*itr).exportAsset();
		}
		else
		{
			wcout << "The format is ilegal";
		}

	}
}

wstring ObjectSet::getTargetPath()
{
	return(targetPath);
}