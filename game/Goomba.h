#pragma once
#include "GameObject.h"
#include "Utils.h"

#define GOOMBA_WALKING_SPEED 0.05f;
#define GOOMBA_DEFLECT_SPEED 0.5f;

#define GOOMBA_BBOX_WIDTH 50
#define GOOMBA_BBOX_HEIGHT 50
#define GOOMBA_BBOX_HEIGHT_DIE 28

#define GOOMBA_STATE_WALKING 100
#define GOOMBA_STATE_DIE 200

#define GOOMBA_ANI_WALKING 0
#define GOOMBA_ANI_DIE 1

#define GOOMBA_DIE_TIME 200
#define GOOMBA_GRAVITY		0.0014f

#define GOOMBA_LEVEL_WALK 1

class CGoomba: public CGameObject
{
protected:
	DWORD dieTimeStart;
	int level;
	bool isOnGround;
public:
	CGoomba();
	void DowngradeLevel();
	void StartDieTime() { dieTimeStart = GetTickCount64(); }
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void SetState(int state);
};

