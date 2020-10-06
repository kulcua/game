#pragma once
#include "GameObject.h"

#define MARIO_WALKING_SPEED		0.05f 
#define MARIO_RUN_SPEED			0.2f 
//0.1f
#define MARIO_JUMP_SPEED_Y		0.5f
#define MARIO_JUMP_DEFLECT_SPEED 0.2f
#define MARIO_GRAVITY			0.002f
#define MARIO_DIE_DEFLECT_SPEED	 0.5f
#define MARIO_ACCELERATION		0.0002f //gia toc

#define MARIO_STATE_IDLE			0
#define MARIO_STATE_WALKING_RIGHT	100
#define MARIO_STATE_WALKING_LEFT	200
#define MARIO_STATE_SIT				300
#define MARIO_STATE_JUMP			400
#define MARIO_STATE_PRE_FLY			500
#define MARIO_STATE_FLY				600
#define MARIO_STATE_STOP			700
#define MARIO_STATE_DIE				999

#define MARIO_ANI_SMALL_IDLE		0 
#define MARIO_ANI_SMALL_WALKING		1
#define MARIO_ANI_SMALL_JUMP		2
#define MARIO_ANI_SMALL_RUN			3
#define MARIO_ANI_SMALL_PRE_FLY		4
#define MARIO_ANI_SMALL_FLY			5
#define MARIO_ANI_SMALL_STOP		6
#define MARIO_ANI_DIE				7 

#define MARIO_ANI_BIG_IDLE			8
#define MARIO_ANI_BIG_WALKING		9
#define MARIO_ANI_BIG_SIT			10
#define MARIO_ANI_BIG_JUMP			11
#define MARIO_ANI_BIG_RUN			12
#define MARIO_ANI_BIG_PRE_FLY		13
#define MARIO_ANI_BIG_FLY			14
#define MARIO_ANI_BIG_STOP			15

#define MARIO_ANI_RACCOON_IDLE		16
#define MARIO_ANI_RACCOON_WALKING	17
#define MARIO_ANI_RACCOON_SIT		18
#define MARIO_ANI_RACCOON_JUMP		19
#define MARIO_ANI_RACCOON_RUN		20
#define MARIO_ANI_RACCOON_PRE_FLY	21
#define MARIO_ANI_RACCOON_FLY		22
#define MARIO_ANI_RACCOON_STOP		23

#define	MARIO_LEVEL_SMALL	1
#define	MARIO_LEVEL_BIG		2
#define	MARIO_LEVEL_RACCOON	3

#define MARIO_SIT_BBOX_HEIGHT 17

#define MARIO_RACCOON_BBOX_WIDTH  24
#define MARIO_RACCOON_BBOX_HEIGHT 27

#define MARIO_BIG_BBOX_WIDTH  15
#define MARIO_BIG_BBOX_HEIGHT 26

#define MARIO_SMALL_BBOX_WIDTH  13
#define MARIO_SMALL_BBOX_HEIGHT 15

#define MARIO_UNTOUCHABLE_TIME 5000

class CMario : public CGameObject
{
	int level;
	int untouchable;
	DWORD untouchable_start;

	float start_x;			// initial position of Mario at scene
	float start_y;

	float a;
	bool isGrounded = false;

public:
	bool isSit = false;
	bool isRun = false;

	CMario(float x = 0.0f, float y = 0.0f);

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_object = NULL);
	virtual void Render();

	void SetState(int state);
	void SetLevel(int l) { level = l; }
	int GetLevel() { return level; }
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }

	void CollisionAABB(vector<LPGAMEOBJECT> *coObjects);
	
	void Reset();

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

