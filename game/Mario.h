#pragma once
#include "GameObject.h"
#include "Utils.h"

#define MARIO_WALKING_SPEED		0.1f 
#define MARIO_RUN_SPEED			0.15f 
#define MARIO_JUMP_SPEED_Y		0.3f
#define MARIO_FLY_SPEED_Y		0.25f
#define MARIO_DROP_FLY_SPEED_Y	0.01f
#define MARIO_JUMP_DEFLECT_SPEED 0.2f
#define MARIO_GRAVITY			0.0007f
#define MARIO_DIE_DEFLECT_SPEED	 0.5f
#define MARIO_ACCELERATION		0.0002f

#define MARIO_STATE_IDLE			0
#define MARIO_STATE_WALKING_RIGHT	100
#define MARIO_STATE_WALKING_LEFT	200
#define MARIO_STATE_SIT				300
#define MARIO_STATE_JUMP			400
#define MARIO_STATE_STOP			500
#define MARIO_STATE_SPIN			600
#define MARIO_STATE_FLY				700
#define MARIO_STATE_DIE				999

#define MARIO_ANI_SMALL_IDLE		0 
#define MARIO_ANI_SMALL_WALKING		1
#define MARIO_ANI_SMALL_JUMP		2
#define MARIO_ANI_SMALL_RUN			3
#define MARIO_ANI_SMALL_PRE_FLY		4
#define MARIO_ANI_SMALL_FLY			5
#define MARIO_ANI_SMALL_STOP		6
#define MARIO_ANI_SMALL_KICK		7
#define MARIO_ANI_SMALL_DROP		8
#define MARIO_ANI_DIE				9 

#define MARIO_ANI_BIG_IDLE			10
#define MARIO_ANI_BIG_WALKING		11
#define MARIO_ANI_BIG_SIT			12
#define MARIO_ANI_BIG_JUMP			13
#define MARIO_ANI_BIG_RUN			14
#define MARIO_ANI_BIG_PRE_FLY		15
#define MARIO_ANI_BIG_FLY			16
#define MARIO_ANI_BIG_STOP			17
#define MARIO_ANI_BIG_KICK			18
#define MARIO_ANI_BIG_DROP			19

#define MARIO_ANI_RACCOON_IDLE		20
#define MARIO_ANI_RACCOON_WALKING	21
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
#define MARIO_RUN_TIME	2000
#define MARIO_KICK_TIME	500
#define MARIO_SPIN_TIME	200

class CMario : public CGameObject
{
	int level;

	int untouchable;
	DWORD untouchable_start;

	DWORD run_start;

	bool kick;
	DWORD kick_start;

	bool level_up;
	DWORD level_up_start;
	
	DWORD spin_start;

	float start_x;			// initial position of Mario at scene
	float start_y;

	float a;
	bool isGrounded;

public:
	bool isSit;
	bool isDrop;
	bool isDropFly;
	bool isJump;
	bool isRun; //check run o keyboard -> doi van toc run
	bool run; //check run hay prefly

	bool isPreFly;
	bool isFly;

	bool spin;

	CMario(float x = 0.0f, float y = 0.0f);

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_object = NULL);
	virtual void Render();

	void SetState(int state);
	void SetLevel(int l) { level = l; }
	int GetLevel() { return level; }

	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }
	void StartRun() {
		if (!run) { run = true;	run_start = GetTickCount(); }
	}
	void StartKick() { kick = true; kick_start = GetTickCount(); }
	void StartSpin() { spin = true; spin_start = GetTickCount(); }
	void StartLevelUp() { level_up = true; level_up_start = GetTickCount(); }

	//void CollisionAABB(vector<LPGAMEOBJECT> *coObjects);
	
	void Reset();

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

