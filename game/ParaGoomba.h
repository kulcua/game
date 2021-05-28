#pragma once
#include "Goomba.h"
#include "Mario.h"

#define PARAGOOMBA_BBOX_FLY_HEIGHT 74
#define PARAGOOMBA_BBOX_WALK_HEIGHT 58

#define PARAGOOMBA_STATE_JUMP 100

#define PARAGOOMBA_ANI_FLYING 0
#define PARAGOOMBA_ANI_WALKING 1
#define PARAGOOMBA_ANI_NO_WING 2
#define PARAGOOMBA_ANI_DIE 3

#define PARAGOOMBA_JUMP_TIMES 4
#define PARAGOOMBA_LOW_JUMP_SPEED 0.3f
#define PARAGOOMBA_HIGH_JUMP_SPEED 0.4f
#define PARAGOOMBA_WALK_TIME 2000

#define	PARAGOOMBA_LEVEL_JUMP 2

class ParaGoomba : public CGoomba
{
	int jumpTimes;
	DWORD walkingTimeStart;
	CMario* mario;
public:
	ParaGoomba();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void SetState(int state);
	void StartWalkingTime() { walkingTimeStart = GetTickCount64(); };
};

