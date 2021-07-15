#pragma once
#include "GameObject.h"
#include "Utils.h"
#include "Card.h"
#define MARIO_WALKING_SPEED		0.2f 
#define MARIO_RUN_SPEED			0.4f 
#define MARIO_JUMP_SPEED_Y		0.7f
#define MARIO_FLY_SPEED_Y		0.6f
#define MARIO_JUMP_FLY_SPEED_Y	0.75f
#define MARIO_DROP_FLY_SPEED_Y	0.02f
#define MARIO_JUMP_DEFLECT_SPEED 0.4f
#define MARIO_GRAVITY			0.002f
#define MARIO_VY_DROP			0.07f
#define MARIO_DIE_DEFLECT_SPEED	 1.0f
#define MARIO_ACCELERATION		0.001f
#define MARIO_STATE_DIE				999
#define MARIO_ANI_SMALL_IDLE		0 
#define MARIO_ANI_SMALL_WALK		1
#define MARIO_ANI_SMALL_JUMP		2
#define MARIO_ANI_SMALL_RUN			3
#define MARIO_ANI_SMALL_PRE_FLY		4
#define MARIO_ANI_SMALL_FLY			5
#define MARIO_ANI_SMALL_STOP		6
#define MARIO_ANI_SMALL_KICK		7
#define MARIO_ANI_SMALL_DROP		8
#define MARIO_ANI_DIE				9 
#define MARIO_ANI_BIG_IDLE			10
#define MARIO_ANI_BIG_WALK			11
#define MARIO_ANI_BIG_SIT			12
#define MARIO_ANI_BIG_JUMP			13
#define MARIO_ANI_BIG_RUN			14
#define MARIO_ANI_BIG_PRE_FLY		15
#define MARIO_ANI_BIG_FLY			16
#define MARIO_ANI_BIG_STOP			17
#define MARIO_ANI_BIG_KICK			18
#define MARIO_ANI_BIG_DROP			19
#define MARIO_ANI_RACCOON_IDLE		20
#define MARIO_ANI_RACCOON_WALK		21
#define MARIO_ANI_RACCOON_SIT		22
#define MARIO_ANI_RACCOON_JUMP		23
#define MARIO_ANI_RACCOON_RUN		24
#define MARIO_ANI_RACCOON_DROP		25
#define MARIO_ANI_RACCOON_PRE_FLY	26
#define MARIO_ANI_RACCOON_FLY		27
#define MARIO_ANI_RACCOON_STOP		28
#define MARIO_ANI_RACCOON_SPIN		29
#define MARIO_ANI_RACCOON_KICK		30
#define MARIO_ANI_RACCOON_DROP_FLY	32
#define MARIO_ANI_ITEM_SMALL_TO_BIG			33
#define MARIO_ANI_ITEM_BIG_TO_RACOON		34
#define MARIO_ANI_SMALL_HANDLESHELL_IDLE			35
#define MARIO_ANI_SMALL_HANDLESHELL_RUN				36
#define MARIO_ANI_SMALL_HANDLESHELL_JUMP_DROP		37
#define MARIO_ANI_BIG_HANDLESHELL_IDLE				38
#define MARIO_ANI_BIG_HANDLESHELL_RUN				39
#define MARIO_ANI_BIG_HANDLESHELL_JUMP_DROP			40
#define MARIO_ANI_RACCOON_HANDLESHELL_IDLE			41
#define MARIO_ANI_RACCOON_HANDLESHELL_RUN			42
#define MARIO_ANI_RACCOON_HANDLESHELL_JUMP_FLY_DROP 43
#define MARIO_ANI_FIRE_IDLE			44
#define MARIO_ANI_FIRE_WALK			45
#define MARIO_ANI_FIRE_SIT			46
#define MARIO_ANI_FIRE_JUMP			47
#define MARIO_ANI_FIRE_RUN			48
#define MARIO_ANI_FIRE_PRE_FLY		49
#define MARIO_ANI_FIRE_FLY			50
#define MARIO_ANI_FIRE_STOP			51
#define MARIO_ANI_FIRE_KICK			52
#define MARIO_ANI_FIRE_DROP			53
#define MARIO_ANI_FIRE_HANDLESHELL_IDLE				54
#define MARIO_ANI_FIRE_HANDLESHELL_RUN				55
#define MARIO_ANI_FIRE_HANDLESHELL_JUMP_DROP		56
#define MARIO_ANI_FIRE_SHOOT_FIREBALL_IDLE				57
#define MARIO_ANI_FIRE_SHOOT_FIREBALL_JUMP				58
#define MARIO_ANI_RACCOON_ROLL	59
#define MARIO_ANI_FRONT_SMALL			60
#define MARIO_ANI_FRONT_BIG				61
#define MARIO_ANI_FRONT_RACCOON			62
#define MARIO_ANI_FRONT_FIRE			63
#define	MARIO_LEVEL_SMALL	1
#define	MARIO_LEVEL_BIG		2
#define	MARIO_LEVEL_RACCOON	3
#define	MARIO_LEVEL_FIRE	4
#define MARIO_SIT_BBOX_HEIGHT 55
#define MARIO_RACCOON_BBOX_WIDTH  65
#define MARIO_RACCOON_BBOX_HEIGHT 86
#define MARIO_BIG_BBOX_WIDTH  42
#define MARIO_BIG_BBOX_HEIGHT 81
#define MARIO_SMALL_BBOX_WIDTH  40
#define MARIO_SMALL_BBOX_HEIGHT 48
#define MARIO_BBOX_TAIL_HIT_RIGHT 30
#define MARIO_BBOX_TAIL_HIT_LEFT 5
#define MARIO_LEVEL_UP_TIME	1100
#define MARIO_KICK_TIME	500
#define MARIO_HIGH_JUMP_TIME 200
#define MARIO_DEFLECT_MUSICAL_NOTE 0.8f
#define MARIO_SPIN_TIME	200
#define MARIO_MAX_POWER	7
#define MARIO_POWERUP_PER_SECOND	200
#define MARIO_ANI_SET_ID	1
#define MARIO_Y_DROP_BEHIND_SCENE	0.2f
#define MARIO_UNTOUCHABLE_TIME	5000
#define MARIO_HOLD_DOWN_TIME	3000
#define MARIO_BEHIND_SCENE_TIME	5000

class CMario : public CGameObject
{
	friend class MarioState;
	friend class CKoopa;
	friend class FireBallPool;
	friend class MarioTail;

	MarioTail* tail;

	CKoopa* koopaShell;
	int level;
	int ani;

	CardType cardType;

	int power;
	int savePower;
	int point = 0;
	int money = 0;
	int alpha = 255;
	ULONGLONG untouchableStartTime;
	ULONGLONG holdDownStartTime;
public:
	bool holdDownKey;
	ULONGLONG behindSceneStartTime;

	ULONGLONG powerStartTime;
	ULONGLONG powerEndTime;

	MarioState* state_;

	int life = 3;
	bool switchItem;

	void HandleInput(Input input);

	bool isPower;
	bool isHandleShell;
	bool isUntouchable;

	CMario();

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_object = NULL);
	virtual void Render();
	void SetState(int state);
	void SetLevel(int l) { level = l; }
	int GetLevel() { return level; }

	void SetPoint(int point) { this->point += point; }
	int GetPoint() { return point; }

	void SetMoney(int money) { this->money += money; }
	int GetMoney() { return money; }

	void SetAnimation(int a) { ani = a; }
	int GetAnimation() { return ani; }

	void PowerUp() { powerStartTime = GetTickCount64(); savePower = 0; }
	void PowerDown() { powerEndTime = GetTickCount64(); savePower = 0; }
	void PowerReset();
	int GetPower() { return power; }
	void PowerControl();
	
	void Reset();

	void LevelUp();
	void LevelDown();
	void StartUntouchable() { untouchableStartTime = GetTickCount64(); }
	void ManageAlphaUntouchable();
	void KickShellAfterHandle();

	void SetLife(int life) { this->life = life; }
	int GetLife() { return life; }

	void SetTail(MarioTail* tail);

	virtual void HandleCollision(vector<LPGAMEOBJECT>* coObjects);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	void SetCardType(CardType card) { cardType = card; nx = 1; }
	CardType GetCardType() { return cardType; }

	void StartHoldDown() { holdDownStartTime = GetTickCount64(); }
	void StartBehindScene() { behindSceneStartTime = GetTickCount64(); }
	void HandleBehindScene();
};