#pragma once
#include "GameObject.h"
#include "Mario.h"

#define MINI_GOOMBA_SPEED_VX 0.2f
#define MINI_GOOMBA_SPEED_VY 0.1f
#define MINI_GOOMBA_SPEED_VX_FL_MARIO 0.1f
#define MINI_GOOMBA_SPEED_VY_FL_MARIO 0.03f
#define MINI_GOOMBA_SPEED_VY_DEFLECT 0.2f
#define MINI_GOOMBA_GRAVITY 0.002f
#define MINI_GOOMBA_BBOX_SIZE 20
#define MINI_GOOMBA_ANI_ID 33
#define MINI_GOOMBA_TIME_FLIP 1000
#define MINI_GOOMBA_TIME_DIE 5500
#define MINI_GOOMBA_UNFOLLOW_JUMP_CHECK_TIME 1000
#define MINI_GOOMBA_JUMP_TIMES 3
#define MINI_GOOMBA_UNFOLLOW_TO_DIE_TIME 3000

class MiniGoomba : public CGameObject
{
	friend class MiniGoombaPool;
	CMario* mario;
	MiniGoomba* next;
	ULONGLONG animateTimeStart;
	ULONGLONG timeToDie;
	ULONGLONG timeFlip;
	int marioJumpTimes;
	ULONGLONG marioJumpTimeStart;
	ULONGLONG unfollowMarioTimeStart;
public:
	MiniGoomba();

	bool inUse;
	bool followMario;

	void Init(float x, float y);
	void CheckUnfollow();
	void StartAnimate();
	void FollowMario();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);

	MiniGoomba* GetNext() const { return next; }
	void SetNext(MiniGoomba* next) { this->next = next; }
	bool GetBackToPool();
};
