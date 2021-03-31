#pragma once

#include <Windows.h>
#include <signal.h>
#include <string>
#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <stdlib.h>
#include <vector>
#include <d3dx9.h>

enum Input {
	NO_INPUT,
	KEY_STATE,
	PRESS_DOWN,
	RELEASE_DOWN,
	PRESS_A,
	RELEASE_A,
	PRESS_S,
	RELEASE_S,
	PRESS_LEFT,
	PRESS_RIGHT,
	RELEASE_LEFT,
	RELEASE_RIGHT
};

using namespace std;

void DebugOut(wchar_t* fmt, ...);

vector<string> split(string line, string delimeter = "\t");
wstring ToWSTR(string st);

LPCWSTR ToLPCWSTR(string st);

