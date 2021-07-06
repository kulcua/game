#pragma once
#include "Enermy.h"
#include "Utils.h"
#include "Boomerang.h"

#define BOOMERANG_BROTHER_WALK_SPEED 0.05f
#define BOOMERANG_BROTHER_JUMP_SPEED 0.2f
#define BOOMERANG_BROTHER_GRAVITY	0.001f
#define BOOMERANG_BROTHER_BBOX_WIDTH 50
#define BOOMERANG_BROTHER_BBOX_HEIGHT 70
#define BOOMERANG_BROTHER_STATE_WALK 100
#define BOOMERANG_BROTHER_STATE_JUMP 200
#define BOOMERANG_BROTHER_STATE_THROW 300
#define BOOMERANG_BROTHER_STATE_DIE 400
#define BOOMERANG_BROTHER_ANI_WALK 0
#define BOOMERANG_BROTHER_ANI_THROW 1
#define BOOMERANG_BROTHER_TIME_WALK_START 3000
#define BOOMERANG_BROTHER_TIME_THROW_1_START 4000
#define BOOMERANG_BROTHER_TIME_THROW_2_START 4500
#define BOOMERANG_BROTHER_DIE_TIME 500

class BoomerangBrother : public Enermy
{
	int moveDirect;
	int timeStart;
public:
	BoomerangBrother();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void SetState(int state);
	void HandleCollision(vector<LPGAMEOBJECT>* coObjects);
	void ChangeState();
};



