#pragma once
#include "stdafx.h"
#include "serialize.h"
#include "tst.h"
#include <fstream>
#define EXPORT_PATH "d:/JsonFile.Json"

void Serialize::exportJson(map<wstring, vector<wstring>> myObjectIDMap, wstring myPath)
{
	//把指定的<objectID : [megaID, megaID, ...]> 输出为 json格式
	//todo : debug 检测， keywordmanager 输出相应的 map格式
	//<Vector>
	Document _document;
	Document::AllocatorType &allocator = _document.GetAllocator();
	_document.SetObject();

	for (map<wstring, vector<wstring>>::iterator itr = myObjectIDMap.begin(); itr != myObjectIDMap.end(); itr++)
	{
		Value _objectId;
		string _objectIdString = Serialize::wStringToUTF8(itr->first);
		//todo: 找一下更简洁的方法
		//产生一个json能用的string value
		//string 转 字符串数组
		const char * _cha = _objectIdString.c_str();
		char buffer[260];
		int _len = sprintf_s(buffer, "%s", _cha);
		_objectId.SetString(buffer, _len, allocator);
		
		Value _array(kArrayType);

		for (vector<wstring>::iterator itr2 = itr->second.begin(); itr2 != itr->second.end(); itr2++)
		{
			Value _megaScaneID;
			string _megaScaneId = Serialize::wStringToUTF8(*itr2);
			const char * _cha = _megaScaneId.c_str();
			char buffer[260];
			int _len = sprintf_s(buffer, "%s", _cha);
			_megaScaneID.SetString(buffer, _len, allocator);
			_array.PushBack(_megaScaneID, allocator);
		}

		_document.AddMember(_objectId, _array, allocator);
	}
	Serialize::exportJsonFile(_document, myPath);
}

bool Serialize::importJson(map<wstring, vector<wstring>> & resultDoc, wstring myFilePath)
{
	//import json 到 <objectID : [megaID, megaID, ...]> 
	//<Vector>
	bool result = false;
	rapidjson::Document _document;
	//todo : path 修改
	result = Serialize::importJsonFile(_document, myFilePath);
	if (result)
	{
		for (Value::ConstMemberIterator itr = _document.MemberBegin(); itr != _document.MemberEnd(); ++itr)
		{
			wstring _wObjectID = Serialize::UTF8ToWString(itr->name.GetString());
			vector<wstring> _megaScanID;

			const Value& _a = itr->value;
			for (Value::ConstValueIterator itrA = _a.Begin(); itrA != _a.End(); itrA++)
			{
				wstring _megaID = Serialize::UTF8ToWString((itrA->GetString()));
				_megaScanID.push_back(_megaID);
			}
			resultDoc[_wObjectID] = _megaScanID;
		}
	}
	return(result);
}

void Serialize::exportWstringMapJson(map<wstring, wstring> myMap, wstring myPath)
{
	//把指定的<use : use> 输出为 json格式
	//todo : debug 检测， keywordmanager 输出相应的 map格式
	//<Vector>
	Document _document;
	Document::AllocatorType &allocator = _document.GetAllocator();
	_document.SetObject();

	for (map<wstring, wstring>::iterator itr = myMap.begin(); itr != myMap.end(); itr++)
	{
		Value name1;
		string megaScanUse = Serialize::wStringToUTF8(itr->first);
		const char * _cha1 = megaScanUse.c_str();
		char buffer1[260];
		int _len1 = sprintf_s(buffer1, "%s", _cha1);
		name1.SetString(buffer1, _len1, allocator);


		Value name2;
		string textetUse = Serialize::wStringToUTF8(itr->second);
		const char * _cha2 = textetUse.c_str();
		char buffer2[260];
		int _len2 = sprintf_s(buffer2, "%s", _cha2);
		name2.SetString(buffer2, _len2, allocator);

		_document.AddMember(name1, name2, allocator);
	}
	Serialize::exportJsonFile(_document, myPath);
}

void Serialize::importWstringMapJson(map<wstring, wstring> & result, wstring myFilePath)
{
	//import json 到 <wstring : wstring> 

	rapidjson::Document _document;
	//todo : path 修改
	Serialize::importJsonFile(_document, myFilePath);

	for (Value::ConstMemberIterator itr = _document.MemberBegin(); itr != _document.MemberEnd(); ++itr)
	{
		wstring _par1 = Serialize::UTF8ToWString(itr->name.GetString());
		wstring _par2 = Serialize::UTF8ToWString(itr->value.GetString());

		result[_par1] = _par2;
	}
}

bool Serialize::importJsonFile(Document & resultDoc , wstring myPath)
{
	bool result = false;
	//support both ASKII and Unicode
	const wchar_t * _path = (wchar_t *)myPath.c_str();

	errno_t err;
	FILE *fp;
	
	err = _wfopen_s(&fp, _path,L"r");
	if (err == 0)
	{
		result = true;
	}
	else
	{
		//wcout << L"[error] failed open: " << myPath << endl;
	}
	char readBuffer[65536];
	rapidjson :: FileReadStream is(fp, readBuffer, sizeof(readBuffer));

	resultDoc.ParseStream(is);
	fclose(fp);
	return(result);
}

bool Serialize::importTst( wstring myPath , Tst & myTst)
{
	bool result = false;
	rapidjson::Document _document;
	result = Serialize::importJsonFile(_document, myPath);
	if (result)
	{
		vector<Value> _source;
		for (Value::ConstMemberIterator itr = _document.MemberBegin(); itr != _document.MemberEnd(); ++itr)
		{
			wstring _tag = Serialize::UTF8ToWString(itr->name.GetString());

			if (_tag == L"Version")
			{
				wstring _v = Serialize::UTF8ToWString(itr->value.GetString());
			}
			else if (_tag == L"Source")
			{
				const Value& source = _document["Source"];
				for (SizeType i = 0; i < source.Size(); i++)
				{
					TstSource _tstSStru;
					const Value& _imageNode = source[i];

					const char * myStrNa = "Name";
					_tstSStru.name = Serialize::UTF8ToWString(_imageNode[myStrNa].GetString());
					const char * myStrFor = "Format";
					_tstSStru.format = Serialize::UTF8ToWString(_imageNode[myStrFor].GetString());
					const char * myStrCS = "ColorSpace";
					_tstSStru.colorSpace = Serialize::UTF8ToWString(_imageNode[myStrCS].GetString());
					const char * myStrID = "DestID";
					_tstSStru.destID = Serialize::UTF8ToWString(_imageNode[myStrID].GetString());
					const char * myStrDc = "DestChannel";
					_tstSStru.destChannerl = Serialize::UTF8ToWString(_imageNode[myStrDc].GetString());
					myTst.sourceNodes.push_back(_tstSStru);
				}

			}
			else if (_tag == L"Dest")
			{
				const Value& target = _document["Dest"];
				for (SizeType i = 0; i < target.Size(); i++)
				{
					TstDest _tstTStru;
					const Value& _imageNode = target[i];

					const char * myStrID = "ID";
					_tstTStru.ID = Serialize::UTF8ToWString(_imageNode[myStrID].GetString());
					const char * myStrNS = "NameSuffix";
					_tstTStru.NameSuffix = Serialize::UTF8ToWString(_imageNode[myStrNS].GetString());
					const char * myStrFo = "Format";
					_tstTStru.Format = Serialize::UTF8ToWString(_imageNode[myStrFo].GetString());
					const char * myStrFT = "FileType";
					_tstTStru.FileType = Serialize::UTF8ToWString(_imageNode[myStrFT].GetString());
					const char * myStrCS = "ColorSpace";
					_tstTStru.ColorSpace = Serialize::UTF8ToWString(_imageNode[myStrCS].GetString());
					const char * myStrFi = "Filter";
					_tstTStru.Filter = Serialize::UTF8ToWString(_imageNode[myStrFi].GetString());
					const char * myStrGM = "GenarateMipmap";
					_tstTStru.GenarateMipmap = Serialize::UTF8ToWString(_imageNode[myStrGM].GetString());
					const char * myStrMF = "MipmapFilter";
					_tstTStru.MipmapFilter = Serialize::UTF8ToWString(_imageNode[myStrMF].GetString());
					const char * myStrSc = "Scale";
					_tstTStru.Scale = Serialize::UTF8ToWString(_imageNode[myStrSc].GetString());
					myTst.destNodes.push_back(_tstTStru);
				}
			}
		}
	}

	return(result);

}

void Serialize::setWstring(Value & myValue , Document & doc , wstring myWStr)
{
	Document::AllocatorType &allocator = doc.GetAllocator();
	string _str = Serialize :: wStringToUTF8(myWStr);
	const char * _cha = _str.c_str();
	char buffer[260];
	int _len1 = sprintf_s(buffer, "%s", _cha);
	myValue.SetString(buffer, _len1, allocator);
}

void Serialize::exportTextet(wstring myPath, Textet myTextet)
{
	//todo : 使用真正的path
	//wstring tempPath = L"d:/我的" + myPath.substr(myPath.rfind(L"/") , myPath.size());

	Document _document;
	Document::AllocatorType &allocator = _document.GetAllocator();
	_document.SetObject();

	Value _destNodes(kArrayType);
	for (vector<TextetDest>::iterator itr = myTextet.destNodes.begin(); itr != myTextet.destNodes.end(); itr++)
	{
		Value node(kObjectType);
		Value filePath;
		setWstring(filePath, _document, (*itr).FilePath);
		node.AddMember("FilePath", filePath, allocator);

		Value iD;
		setWstring(iD, _document, (*itr).ID);
		node.AddMember("ID", iD, allocator);
		
		Value scale;
		setWstring(scale, _document, (*itr).Scale);
		node.AddMember("Scale", scale, allocator);

		_destNodes.PushBack(node, allocator);
	}
	_document.AddMember("Dest", _destNodes, allocator);

	Value _sourceNodes(kArrayType);
	for (vector<TextetSource>::iterator itr = myTextet.sourceNodes.begin(); itr != myTextet.sourceNodes.end(); itr++)
	{
		Value node(kObjectType);
		Value filePath;
		setWstring(filePath, _document, (*itr).FilePath);
		node.AddMember("FilePath", filePath, allocator);


		Value name;
		setWstring(name, _document, (*itr).Name);
		node.AddMember("Name", name, allocator);
		_sourceNodes.PushBack(node, allocator);
	}
	_document.AddMember("Source", _sourceNodes, allocator);

	Value textureSetType;
	setWstring(textureSetType, _document, myTextet.textureSetType);
	_document.AddMember("TextureSetType", textureSetType, allocator);

	Value version;
	setWstring(version, _document, myTextet.version);
	_document.AddMember("Version", version, allocator);

	Serialize::exportJsonFile(_document, myPath);
}

void Serialize :: exportJsonFile(rapidjson::Document & myDoc, wstring myPath)
{
	// Serialize::exportJsonFile(document);
	const wchar_t * _path = (wchar_t *)myPath.c_str();

	StringBuffer buffer;
	PrettyWriter<StringBuffer>  writer(buffer);
	myDoc.Accept(writer);

	std::string strJson = buffer.GetString();

	wofstream myFile;
	myFile.open(_path);
	if (myFile.is_open())
	{
		myFile << buffer.GetString() << endl;
	}
}

void makeJsonObj()
{
	//处理使用 string variable 的例子
	Document document;
	Document::AllocatorType &allocator = document.GetAllocator();

	Value author;
	string myStr = "lalaji";
	const char * myCha = myStr.c_str();//string 转 字符串数组
	char buffer[10];
	int len = sprintf_s(buffer, "%s", myStr);
	cout << myCha << endl;

	author.SetString(buffer, len, document.GetAllocator());

	cout << author.GetString() << endl;
	printf("__________");

	Value val(42);                             // 某 Value
	document.AddMember(author, val, document.GetAllocator());
	printf("%i", document[author].GetInt());
	printf("%i", document["lalaji"].GetInt());

}

void makeJsonObj2() 
{
	//字符串建立 json object的例子
	rapidjson :: Document document;
	//建立char的json object
	//const char json[] = " { \"hello\" : \"world\", \"t\" : true , \"f\" : false, \"n\": null, \"i\":123, \"pi\": 3.1416, \"a\":[1, 2, 3, 4] } ";
	const WCHAR* wc = L" { \"hello\" : \"world\", \"t\" : true , \"f\" : false, \"n\": null, \"i\":123, \"pi\": 3.1416, \"a\":[\"辣\", \"的\"] } ";
	//转换wchar_t为 char
	_bstr_t b(wc);
	const char* json = b;

	//建立Json文档 这里只能接受char
	document.Parse(json);
	assert(document.IsObject());

	//取得字符串方法
	assert(document["hello"].IsString());
	printf("hello = %s\n", document["hello"].GetString());
	// 取得bool方法
	assert(document["t"].IsBool());
	printf("t = %s\n", document["t"].GetBool() ? "true" : "false");
	const rapidjson :: Value& a = document["a"];
	assert(a.IsArray());
	cout << (a.IsArray());
	for (rapidjson::SizeType i = 0; i < a.Size(); i++) // Uses SizeType instead of size_t
	{
		//wstring myWS = "你好";
		wcout << a[i].GetString() << endl;
		//printf("a[%d] = %d\n", i, a[i].GetInt());
		
	}
}

std::string Serialize::wStringToUTF8(wstring myWString)
{
	wchar_t * lpwcszWString = (wchar_t *)(myWString).c_str();
	char* pElementText;
	int iTextLen = ::WideCharToMultiByte(CP_UTF8, 0, (LPWSTR)lpwcszWString, -1, NULL, 0, NULL, NULL);
	pElementText = new char[iTextLen + 1];
	memset((void*)pElementText, 0, (iTextLen + 1) * sizeof(char));
	::WideCharToMultiByte(CP_UTF8, 0, (LPWSTR)lpwcszWString, -1, pElementText, iTextLen, NULL, NULL);
	std::string strReturn(pElementText);
	delete[] pElementText;
	return strReturn;
}

std::wstring Serialize::UTF8ToWString(string myString)
{
	char * lpcszString = (char *)(myString).c_str();
	int len = strlen(lpcszString);
	int unicodeLen = ::MultiByteToWideChar(CP_UTF8, 0, lpcszString, -1, NULL, 0);
	wchar_t* pUnicode;
	pUnicode = new wchar_t[unicodeLen + 1];
	memset((void*)pUnicode, 0, (unicodeLen + 1) * sizeof(wchar_t));
	::MultiByteToWideChar(CP_UTF8, 0, lpcszString, -1, (LPWSTR)pUnicode, unicodeLen);
	wstring wstrReturn(pUnicode);
	delete[] pUnicode;
	return wstrReturn;
}

void Serialize::printUTF8(string myUTF8String)
{
	system("chcp 65001"); //设置字符集 （使用SetConsoleCP(65001)设置无效，原因未知）  

	CONSOLE_FONT_INFOEX info = { 0 }; // 以下设置字体  
	info.cbSize = sizeof(info);
	info.dwFontSize.Y = 16; // leave X as zero  
	info.FontWeight = FW_NORMAL;
	wcscpy_s(info.FaceName, L"Consolas");
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), NULL, &info);
	printf("%s\n", myUTF8String);
}

wstring Serialize::mbToWcs(const string &myString)
{
	std::string curLocale = setlocale(LC_ALL, "");
	const char * _Source = myString.c_str();
	size_t _Dsize = mbstowcs(NULL, _Source, 0) + 1;
	wchar_t *_Dest = new wchar_t[_Dsize];
	wmemset(_Dest, 0, _Dsize);
	mbstowcs(_Dest, _Source, _Dsize);
	std::wstring result = _Dest;
	delete[]_Dest;
	setlocale(LC_ALL, curLocale.c_str());
	return result;
}
