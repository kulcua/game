#pragma once
#include "GameObject.h"
#include "Utils.h"

class CMario : public CGameObject
{
	friend class MarioState;

	int level;
	int ani;

	int power;
	int save_power;

	int untouchable;
	DWORD untouchable_start;

	float start_x;			// initial position of Mario at scene
	float start_y;
public:
	DWORD power_time_start;
	DWORD power_time_end;

	bool isGrounded;
	bool isPower;
	MarioState* state_;

	void HandleInput(Input input);

	bool isSit;
	bool highJump;
	bool isAttack;

	CMario(float x = 0.0f, float y = 0.0f);

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_object = NULL);
	virtual void Render();

	void SetState(int state);
	void SetLevel(int l) { level = l; }
	int GetLevel() { return level; }

	void SetAnimation(int a) { ani = a; }
	int GetAnimation() { return ani; }

	void PowerUp() { power_time_start = GetTickCount64(); save_power = 0; }
	void PowerDown() { power_time_end = GetTickCount64(); }
	void PowerReset();
	int GetPower() { return power; }
	void PowerControl();

	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount64(); }

	//void CollisionAABB(vector<LPGAMEOBJECT> *coObjects);
	
	void Reset();

	void LevelUp();

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};