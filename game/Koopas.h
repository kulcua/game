#pragma once

#include "GameObject.h"

#define KOOPAS_WALKING_SPEED 0.02f
#define KOOPAS_BALL_SPEED 0.1f
#define KOOPAS_GRAVITY	0.002f

#define KOOPAS_BBOX_WIDTH 16
#define KOOPAS_BBOX_HEIGHT 24
#define KOOPAS_BBOX_HEIGHT_DIE 16

#define KOOPAS_STATE_WALKING 100
#define KOOPAS_STATE_BALL 200
#define KOOPAS_STATE_DIE 300

#define KOOPAS_ANI_WALKING 0
#define KOOPAS_ANI_BALL 1
#define KOOPAS_ANI_DIE 2

class CKoopas: public CGameObject
{
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
public:
	CKoopas();
	virtual void SetState(int state);
};

