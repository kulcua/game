#pragma once
#include "Enermy.h"
#include "Utils.h"
#define KOOPA_WALKING_SPEED 0.04f
#define KOOPA_BALL_SPEED 0.4f
#define KOOPA_GRAVITY	0.001f
#define KOOPA_BBOX_WIDTH 50
#define KOOPA_BBOX_HEIGHT 82
#define KOOPA_BBOX_HEIGHT_DIE 45
#define KOOPA_STATE_WALKING 100
#define KOOPA_STATE_BALL 200
#define KOOPA_STATE_BALL_RELIVE 300
#define KOOPA_STATE_DIE 400
#define KOOPA_ANI_WALKING 0
#define KOOPA_ANI_BALL 1
#define KOOPA_ANI_BALL_ROLL 2
#define KOOPA_ANI_BALL_RELIVE 3
#define MARIO_BIG_RACCOON_HANDLED_SHELL_HEIGHT 16
#define MARIO_SMALL_HANDLED_SHELL_HEIGHT 4
#define MARIO_SMALL_BIG_RACCOON_HANDLE_SHELL_WIDTH_LEFT 24
#define MARIO_SMALL_BIG_HANDLE_SHELL_WIDTH_RIGHT 20
#define MARIO_RACCOON_HANDLE_SHELL_WIDTH_RIGHT 36
#define KOOPA_LEVEL_BALL 1
#define KOOPA_LEVEL_NO_WING 2
#define KOOPA_LEVEL_WING 3
#define KOOPA_BALL_RELIVE_TIME 4000

class CKoopa: public Enermy
{
protected:
	int level;
	int ballStartTime;
	int reliveStartTime;
public:
	bool isKicked;
	bool isHandled;
	CKoopa();
	void HandleByMario();
	void SetPositionHandled();
	void KickByMario();
	virtual void SetState(int state);
	void WalkThrough();
	void DowngradeLevel();
	void SetLevel(int lv) { this->level = lv; }
	int GetLevel() { return level; }
	void TurnBack(float vx);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void HandleCollision(vector<LPGAMEOBJECT>* coObjects);
	void StartBallTime() { ballStartTime = GetTickCount64(); }
	void StartReliveTime() { reliveStartTime = GetTickCount64(); }
};

