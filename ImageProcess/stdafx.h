// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <stdlib.h>
#include <assert.h>
#include <vector>

#include <stdio.h>
#include <tchar.h>


#include <iostream>
#include <fstream>

//file manager
#include <windows.h>
#include <strsafe.h>
#include "fileManager.h"

//serialize
#include <comdef.h>
#include "serialize.h"

//keywordManager
#include "keywordManager.h"
#define MAX_KEYWORD_SIZE 50

//Utils
#include "utils.h"

//Log
#include "log.h"
#define LOG_PATH  "d:/log.txt"

using namespace std;

#define MAX_PROCESS_FOLDER_NUMBER 300
//path
//公司环境
#define OFFICE_SOURCE_FOLDER L"e:/nicholas_rwc_jx4_data/depot/JX4_SourceData/Graphics/Megascans/surfaces/"
#define OFFICE_TARGET_FOLDER L"d:/我的/"
#define OFFICE_TOOL_FOLDER L"d:"
//家里环境
#define HOME_SOURCE_FOLDER L"F:/我的/surfaces/"
#define HOME_TARGET_FOLDER L"d:/MegascansExport/"
#define HOME_TOOL_FOLDER L"d:"

//TOOL Json file
#define KEYWORD_JSON L"fileKW.json"
#define IDMAP_JSON L"IDMAP.json"
#define DICTION_TXT L"en-dictionary.txt"
#define LOG_TXT L"log.txt"

#pragma comment(lib, "User32.lib")


// TODO: reference additional headers your program requires here
