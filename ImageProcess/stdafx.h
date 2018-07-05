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

//object set
#include "objectSet.h"

using namespace std;

#define MAX_PROCESS_FOLDER_NUMBER 300

#define SUBFOLDER L"surfaces"

//TOOL Json file
#define KEYWORD_JSON L"fileKW.json"
#define IDMAP_JSON L"IDMAP.json"
#define DICTION_TXT L"en-dictionary.txt"
#define USAGENAME_JSON L"usageNameMap.json"
#define LOG_TXT L"log.txt"
#define PATH_INI L"WorkingPath.ini"

#pragma comment(lib, "User32.lib")
