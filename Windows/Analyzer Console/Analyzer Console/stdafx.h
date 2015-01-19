// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

#include <Windows.h>



// TODO: reference additional headers your program requires here
const int BLACK = 0x0000;
const int BLUE = 0x0001 | 0x0008;
const int GREEN = 0x0002 | 0x0008;
const int CYAN = 0x0003 | 0x0008;
const int RED = 0x0004 | 0x0008;
const int MAGENTA = 0x0005 | 0x0008;
const int YELLOW = 0x0006 | 0x0008;
const int WHITE = 0x0007 | 0x0008;

const int BGWHITE = 0x0070 | 0x0080;
const int BGBLACK = 0x0000 | 0x0000;
const int BGGRAY = 0x0070;