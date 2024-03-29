#pragma once
#include "ParaGoomba.h"
#define PARAMINIGOOMBA_FLY_SPEED 0.7f
#define PARAMINIGOOMBA_VX_SPEED 0.1f
#define PARAMINIGOOMBA_VY_THROW_SPEED 0.1f
#define PARAMINIGOOMBA_MAX_Y_TO_MARIO 300
#define PARAMINIGOOMBA_STATE_WALK	500
#define PARAMINIGOOMBA_STATE_FLY	600
#define PARAMINIGOOMBA_STATE_THROW_MINI 700
#define PARAMINIGOOMBA_MAX_THROW_TIME 4
#define PARAMINIGOOMBA_TIME_SPACE_THROW 500
#define PARAMINIGOOMBA_TIME_WALK 4000
#define PARAMINIGOOMBA_MAX_X_TO_MARIO 200
#define PARAMINIGOOMBA_MIN_Y_TO_MARIO 280

class ParaMiniGoomba : public ParaGoomba
{
	ULONGLONG timeStart = GetTickCount64();
	int throwGoombaTimes = PARAMINIGOOMBA_MAX_THROW_TIME;
	ULONGLONG timeThrowStart = 0;
	bool maxY = 0;
public:
	ParaMiniGoomba();
	void ChangeState();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void SetState(int state);
	void Render();
	void StartTimeThrow() { timeThrowStart = GetTickCount64(); }
};
