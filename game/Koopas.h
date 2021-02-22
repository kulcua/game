#pragma once
class CMario;
#include "GameObject.h"

#define KOOPAS_WALKING_SPEED 0.02f
#define KOOPAS_BALL_SPEED 0.2f
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

#define MARIO_BIG_RACCOON_HANDLED_SHELL_HEIGHT 8
#define MARIO_SMALL_HANDLED_SHELL_HEIGHT 2
#define MARIO_SMALL_BIG_RACCOON_HANDLE_SHELL_WIDTH_LEFT 12
#define MARIO_SMALL_BIG_HANDLE_SHELL_WIDTH_RIGHT 10
#define MARIO_RACCOON_HANDLE_SHELL_WIDTH_RIGHT 18

class CKoopas: public CGameObject
{
	float start_x, end_x;
	bool isHandled;
	CMario* mario_;
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
public:
	CKoopas(float start_x, float end_x);
	void HandleByMario(CMario* mario);
	void SetPositionHandled();
	void KickByMario(CMario* mario);
	virtual void SetState(int state);
};

