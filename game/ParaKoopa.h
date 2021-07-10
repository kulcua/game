#pragma once
#include "Koopa.h"

#define PARAKOOPA_BBOX_JUMP_HEIGHT 82
#define PARAKOOPA_ANI_WALK 0
#define PARAKOOPA_ANI_BALL 1
#define PARAKOOPA_ANI_BALL_ROLL 2
#define PARAKOOPA_ANI_BALL_RELIVE	3
#define PARAKOOPA_ANI_JUMP 4
#define PARAKOOPA_STATE_JUMP 700
#define PARAKOOPA_JUMP_SPEED 0.4f

class ParaKoopa : public CKoopa
{
public:
	ParaKoopa();
	virtual void SetState(int state);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
};

