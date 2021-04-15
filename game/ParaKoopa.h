#pragma once
#include "Koopas.h"

#define PARAKOOPA_BBOX_JUMP_HEIGHT 82

#define PARAKOOPA_ANI_JUMP 0
#define PARAKOOPA_ANI_WALK 1
#define PARAKOOPA_ANI_BALL 2
#define PARAKOOPA_ANI_BALL_ROLL 3

#define PARAKOOPA_STATE_JUMP 400

#define PARAKOOPA_JUMP_SPEED 0.4f

#define PARAKOOPA_LEVEL_JUMP 2

class ParaKoopa : public CKoopas
{
public:
	ParaKoopa();
	virtual void SetState(int state);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
};

