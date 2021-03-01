#pragma once
#include "GameObject.h"
#include "Utils.h"

class CMario : public CGameObject
{
	friend class MarioState;
	friend class CKoopas;
	friend class FireBallPool;

	CKoopas* koopaShell;
	int level;
	int ani;

	int power;
	int savePower;

	int untouchable;
	DWORD untouchable_start;

	float start_x;			// initial position of Mario at scene
	float start_y;
public:
	DWORD powerStartTime;
	DWORD powerEndTime;

	bool isGrounded;
	bool isPower;
	bool isHandleShell;
	MarioState* state_;
	FireBallPool* pool_;

	void HandleInput(Input input);

	bool isSit;
	bool isHighJump;
	bool isAttack;

	CMario(float x, float y, FireBallPool* pool);

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_object = NULL);
	virtual void Render();

	void SetState(int state);
	void SetLevel(int l) { level = l; }
	int GetLevel() { return level; }

	void SetAnimation(int a) { ani = a; }
	int GetAnimation() { return ani; }

	void PowerUp() { powerStartTime = GetTickCount64(); savePower = 0; }
	void PowerDown() { powerEndTime = GetTickCount64(); }
	void PowerReset();
	int GetPower() { return power; }
	void PowerControl();

	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount64(); }

	//void CollisionAABB(vector<LPGAMEOBJECT> *coObjects);
	
	void Reset();
	void LevelUp();
	void KickShell();

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};