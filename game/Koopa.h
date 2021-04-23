#pragma once
class CMario;
#include "GameObject.h"
#include "Utils.h"

#define KOOPA_WALKING_SPEED 0.04f
#define KOOPA_BALL_SPEED 0.4f
#define KOOPA_DEFECT_SPEED 0.5f
#define KOOPA_GRAVITY	0.001f

#define KOOPA_BBOX_WIDTH 50
#define KOOPA_BBOX_HEIGHT 82
#define KOOPA_BBOX_HEIGHT_DIE 50

#define KOOPA_STATE_WALKING 100
#define KOOPA_STATE_BALL 200

#define KOOPA_ANI_WALKING 0
#define KOOPA_ANI_BALL 1
#define KOOPA_ANI_BALL_ROLL 2

#define MARIO_BIG_RACCOON_HANDLED_SHELL_HEIGHT 16
#define MARIO_SMALL_HANDLED_SHELL_HEIGHT 4
#define MARIO_SMALL_BIG_RACCOON_HANDLE_SHELL_WIDTH_LEFT 24
#define MARIO_SMALL_BIG_HANDLE_SHELL_WIDTH_RIGHT 20
#define MARIO_RACCOON_HANDLE_SHELL_WIDTH_RIGHT 36

#define KOOPA_LEVEL_BALL 0
#define KOOPA_LEVEL_WALK 1

class CKoopa: public CGameObject
{
protected:
	bool isHandled;
	bool isOnGround;
	CMario* mario_;
	int level;
public:
	CKoopa();
	void HandleByMario(CMario* mario);
	void SetPositionHandled();
	void KickByMario(CMario* mario);
	virtual void SetState(int state);
	void DowngradeLevel();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void HandleCollision(vector<LPGAMEOBJECT>* coObjects);
};

