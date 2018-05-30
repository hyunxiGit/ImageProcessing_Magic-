// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

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
//json
#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"
#include "rapidjson/filewritestream.h"
#include "rapidjson/writer.h"
#include <stdio.h> //json file读

//keywordManager
#include "keywordManager.h"
#define MAX_KEYWORD_SIZE 50

//Asset2D
#include <Magick++.h>
#include "Asset2D.h"

//Utils
#include "utils.h"

//Log
#include "log.h"
#define LOG_PATH  "d:/log.txt"

using namespace Magick;
using namespace std;

#define MAX_PROCESS_FOLDER_NUMBER 300

#pragma comment(lib, "User32.lib")

// TODO: reference additional headers your program requires here
