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

#define MARIO_WALKING_SPEED		0.1f 
#define MARIO_RUN_SPEED			0.15f 
#define MARIO_JUMP_SPEED_Y		0.2f
#define MARIO_FLY_SPEED_Y		0.25f
#define MARIO_DROP_FLY_SPEED_Y	0.01f
#define MARIO_JUMP_DEFLECT_SPEED 0.2f
#define MARIO_GRAVITY			0.0007f
#define MARIO_DIE_DEFLECT_SPEED	 0.5f
#define MARIO_ACCELERATION		0.0002f

#define MARIO_STATE_DIE				999

#define MARIO_ANI_SMALL_IDLE		0 
#define MARIO_ANI_SMALL_WALK		1
#define MARIO_ANI_SMALL_JUMP		2
#define MARIO_ANI_SMALL_RUN			3
#define MARIO_ANI_SMALL_PRE_FLY		4
#define MARIO_ANI_SMALL_FLY			5
#define MARIO_ANI_SMALL_STOP		6
#define MARIO_ANI_SMALL_KICK		7
#define MARIO_ANI_SMALL_DROP		8
#define MARIO_ANI_DIE				9 

#define MARIO_ANI_BIG_IDLE			10
#define MARIO_ANI_BIG_WALK			11
#define MARIO_ANI_BIG_SIT			12
#define MARIO_ANI_BIG_JUMP			13
#define MARIO_ANI_BIG_RUN			14
#define MARIO_ANI_BIG_PRE_FLY		15
#define MARIO_ANI_BIG_FLY			16
#define MARIO_ANI_BIG_STOP			17
#define MARIO_ANI_BIG_KICK			18
#define MARIO_ANI_BIG_DROP			19

#define MARIO_ANI_RACCOON_IDLE		20
#define MARIO_ANI_RACCOON_WALK		21
#define MARIO_ANI_RACCOON_SIT		22
#define MARIO_ANI_RACCOON_JUMP		23
#define MARIO_ANI_RACCOON_RUN		24
#define MARIO_ANI_RACCOON_DROP		25
#define MARIO_ANI_RACCOON_PRE_FLY	26
#define MARIO_ANI_RACCOON_FLY		27
#define MARIO_ANI_RACCOON_STOP		28
#define MARIO_ANI_RACCOON_SPIN		29
#define MARIO_ANI_RACCOON_KICK		30
#define MARIO_ANI_RACCOON_DROP		31
#define MARIO_ANI_RACCOON_DROP_FLY	32

#define MARIO_ANI_ITEM_SMALL_TO_BIG	33
#define MARIO_ANI_ITEM_BOOM			34

#define	MARIO_LEVEL_SMALL	1
#define	MARIO_LEVEL_BIG		2
#define	MARIO_LEVEL_RACCOON	3

#define MARIO_LEVEL_MIN	1
#define MARIO_LEVEL_MAX 3

#define MARIO_SIT_BBOX_HEIGHT 17

#define MARIO_RACCOON_BBOX_WIDTH  24
#define MARIO_RACCOON_BBOX_HEIGHT 27

#define MARIO_BIG_BBOX_WIDTH  15
#define MARIO_BIG_BBOX_HEIGHT 26

#define MARIO_SMALL_BBOX_WIDTH  13
#define MARIO_SMALL_BBOX_HEIGHT 15

#define MARIO_UNTOUCHABLE_TIME 1500
#define MARIO_LEVEL_UP_TIME	1100
#define MARIO_KICK_TIME	500
#define MARIO_HIGH_JUMP_TIME 200
#define MARIO_SPIN_TIME	200

#define MARIO_MAX_POWER	6
#define MARIO_POWERUP_PER_SECOND	200

enum Input {
	KEY_STATE,
	PRESS_DOWN,
	RELEASE_DOWN,
	PRESS_A,
	RELEASE_A,
	PRESS_S,
	RELEASE_S,
	PRESS_LEFT,
	PRESS_RIGHT
};

using namespace std;

void DebugOut(wchar_t* fmt, ...);

vector<string> split(string line, string delimeter = "\t");
wstring ToWSTR(string st);

LPCWSTR ToLPCWSTR(string st);

