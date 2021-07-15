#include <algorithm>
#include <cstdlib>
#include "Mario.h"
#include "Game.h"
#include "Goomba.h"
#include "Enermy.h"
#include "Portal.h"
#include "BigBox.h"
#include "MarioLevelDownState.h"
#include "Ground.h"
#include "Koopa.h"
#include "MarioState.h"
#include "MarioStandingState.h"
#include "MarioTailHitState.h"
#include "MarioKickState.h"
#include "MarioLevelUpState.h"
#include "MarioDroppingState.h"
#include "FireBallPool.h"
#include "CameraBound.h"
#include "KoopaBound.h"
#include "BrotherBound.h"
#include "EffectPool.h"
#include "MarioSittingState.h"
#include "PowerUpItem.h"
#include "MarioTail.h"
#include "BrickBlock.h"
#include "Coin.h"
#include "GreenMushroom.h"
#include "Plant.h"
#include "PortalPipe.h"
#include "Camera.h"
#include "MarioFrontState.h"
#include "MarioOverWorldState.h"
#include "Portal.h"
#include "SwitchItem.h"
#include "MusicalNote.h"
#include "BrickCoins.h"
#include "FireBall.h"
#include "Plant.h"
#include "Boomerang.h"
#include "BoomerangBrother.h"
#include "MiniGoomba.h"

void CMario::HandleCollision(vector<LPGAMEOBJECT>* coObjects)
{
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);

	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float nx = 0, ny;
		FilterCollision(coEvents, coEventsResult, nx, ny);

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<CGoomba*>(e->obj))
			{
				CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);
				if (goomba->GetState() != GOOMBA_STATE_DIE)
				{
					if (e->ny < 0)
					{
						goomba->DowngradeLevel();
						vy = -MARIO_JUMP_DEFLECT_SPEED;
					}
					else LevelDown();
				}
			}
			else if (dynamic_cast<MiniGoomba*>(e->obj))
			{
				MiniGoomba* mGoomba = dynamic_cast<MiniGoomba*>(e->obj);
				mGoomba->folowMario = true;
			}
			else if (dynamic_cast<CKoopa*>(e->obj))
			{
				CKoopa* koopa = dynamic_cast<CKoopa*>(e->obj);
				if (koopa->GetLevel() > KOOPA_LEVEL_BALL) {
					if (e->ny < 0)
					{
						koopa->DowngradeLevel();
						vy = -MARIO_JUMP_DEFLECT_SPEED;
					}
					else if (koopa->GetState() != KOOPA_STATE_DIE)
						LevelDown();
				}
				else
				{
					if (isPower && e->nx != 0) //handleShell
					{
						isHandleShell = true;
						koopa->HandleByMario();
						koopaShell = koopa;
					}
					else { // kick normally
						if (koopa->vx == 0)
						{
							koopa->KickByMario();
							MarioState::kick.GetInstance()->StartKick();
							state_ = MarioState::kick.GetInstance();
						}
						// mario is pushed
						else LevelDown();
					}
				}
			}
			else if (dynamic_cast<CFireBall*>(e->obj)
				|| dynamic_cast<Boomerang*>(e->obj))
			{
				LevelDown();
				e->obj->die = true;
			}
			else if (dynamic_cast<CPlant*>(e->obj))
			{
				LevelDown();
			}
			else if (dynamic_cast<BoomerangBrother*>(e->obj))
			{
				BoomerangBrother* bmrBrother = dynamic_cast<BoomerangBrother*>(e->obj);
				if (bmrBrother->GetState() != BOOMERANG_BROTHER_STATE_DIE)
				{
					if (e->ny < 0)
					{
						bmrBrother->SetState(BOOMERANG_BROTHER_STATE_DIE);
						vy = -MARIO_JUMP_DEFLECT_SPEED;
					}
					else LevelDown();
				}
			}
			else if (dynamic_cast<CBigBox*>(e->obj))
			{
				CBigBox* box = dynamic_cast<CBigBox*>(e->obj);
				if (e->nx)
					x += dx;
				if (e->ny < 0 && holdDownKey && box->GetType() == 2)
				{
					holdDownKey = false;
					StartHoldDown();
				}
			}
			else if (dynamic_cast<Card*>(e->obj))
			{
				Card* card = dynamic_cast<Card*>(e->obj);
				if (e->ny)
				{
					SetCardType(card->RandomCard());
					CGame::GetInstance()->GetCurrentScene()->isFinished = true;
				}
			}
			else if (dynamic_cast<CBrick*>(e->obj))
			{
				CBrick* brick = dynamic_cast<CBrick*>(e->obj);
				if (e->ny > 0)
				{
					MarioJumpingState::GetInstance()->isHighJump = false;
					if (brick->GetState() != BRICK_STATE_DISABLE)
					{
						if (brick->GetLevel() == BRICK_LEVEL_1_ITEM)
							brick->SetState(BRICK_STATE_DISABLE);
						else {
							BrickCoins* brick = dynamic_cast<BrickCoins*>(e->obj);
							brick->SetState(BRICK_STATE_THROW_ITEM);
						}
					}
				}
			}
			else if (dynamic_cast<MusicalNote*>(e->obj))
			{
				MusicalNote* note = dynamic_cast<MusicalNote*>(e->obj);
				note->Deflect(e->ny);
				
				if (e->ny < 0)
				{
					if (note->isHidden == false)
					{
						state_ = MarioState::jumping.GetInstance();
						isOnGround = false;
						if (note->GetType() == MUSICAL_NOTE_TYPE_RED)
						{
							vy = -MARIO_DEFLECT_MUSICAL_NOTE * 3;
							vx = 0;
						}
						else vy = -MARIO_DEFLECT_MUSICAL_NOTE;
					}
				}
				else if (e->ny > 0) {
					MarioState::jumping.GetInstance()->isHighJump = false;
					if (note->GetType() == MUSICAL_NOTE_TYPE_RED && note->isHidden)
						note->isHidden = false;
				}
			}
			else if (dynamic_cast<CCameraBound*>(e->obj))
			{
				if (e->ny > 0)
				{
					state_ = MarioState::dropping.GetInstance();
					PowerReset();
				}
				else if (e->ny < 0)
					isOnGround = true;
			}
			else if (dynamic_cast<CCamera*>(e->obj))
			{
				if (e->ny < 0)
				{
					y += dy;
				}
			}
			else if (dynamic_cast<KoopaBound*>(e->obj) || dynamic_cast<BrotherBound*>(e->obj))
			{
				if (e->nx) x += dx;
				if (e->ny) y += dy;
			}
			else if (dynamic_cast<PowerUpItem*>(e->obj))
			{
				e->obj->die = true;
				LevelUp();
			}
			else if (dynamic_cast<SwitchItem*>(e->obj))
			{
				SwitchItem* sItem = dynamic_cast<SwitchItem*>(e->obj);
				if (sItem->GetState() != SWITCH_STATE_DISABLE)
				{
					sItem->SetState(SWITCH_STATE_DISABLE);
					switchItem = true;
				}
				else {
					y += dy;
				}
			}
			else if (dynamic_cast<GreenMushroom*>(e->obj))
			{
				e->obj->die = true;
				SetLife(life++);
				Effect* effect = EffectPool::GetInstance()->Create();
				if (effect != NULL)
					effect->InitPoint(EffectPoint::p1000, x, y);
			}
			else if (dynamic_cast<Coin*>(e->obj))
			{
				e->obj->die = true;
				SetPoint(100);
				SetMoney(1);
			}
			else if (dynamic_cast<BrickBlock*>(e->obj))
			{
				BrickBlock* block = dynamic_cast<BrickBlock*>(e->obj);
				if (block->isCoin)
				{
					SetPoint(100);
					SetMoney(1);
					block->die = true;
				}
			}
			else if (dynamic_cast<PortalPipe*>(e->obj))
			{
				PortalPipe* port = dynamic_cast<PortalPipe*>(e->obj);
				if (e->ny)
				{
					if (e->ny < 0)
						isOnGround = true;
					if (port->GetName() == PortalName::in)
						MarioFrontState::GetInstance()->GetPortal(*this, port, e->ny);
					else
						MarioFrontState::GetInstance()->onPortalPipe = false;
				}
			}
			else if (dynamic_cast<CPortal*>(e->obj))
			{
				CPortal* port = dynamic_cast<CPortal*>(e->obj);
				x = port->x;
				y = port->y;
				MarioState::overworld.GetInstance()->SetSceneId(port->GetSceneId());
				break;
			}

			if (untouchableStartTime)
			{
				if (dynamic_cast<Enermy*>(e->obj))
					if (nx != 0) x += dx;
			}

			if (dynamic_cast<CGround*>(e->obj)
				|| dynamic_cast<CBigBox*>(e->obj)
				|| dynamic_cast<CBrick*>(e->obj)
				|| dynamic_cast<BrickBlock*>(e->obj))
			{
				if (e->ny < 0)
				{
					MarioFrontState::GetInstance()->onPortalPipe = false;
					isOnGround = true;
				}
			}
		}
	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CMario::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{	
	CGameObject::Update(dt);

	HandleCollision(coObjects);

	if (dynamic_cast<MarioOverWorldState*>(state_) == false)
		vy += MARIO_GRAVITY * dt;

	if (isHandleShell)
	{
		if (koopaShell->GetState() != KOOPA_STATE_BALL)
		{
			isHandleShell = false;
			koopaShell->isHandled = false;
			koopaShell = NULL;
		}
	}

	PowerControl();

	HandleBehindScene();

	tail->Update(dt, coObjects);

	ManageAlphaUntouchable();

	// put it finally because of switch scene delete all objects
	state_->Update(*this, dt);
}

void CMario::HandleBehindScene()
{
	if (holdDownStartTime > 0 && GetTickCount64() - holdDownStartTime > MARIO_HOLD_DOWN_TIME)
	{
		behindSceneStartTime = GetTickCount64();
		holdDownStartTime = 0;
		y += 0.5f;
	}

	if (behindSceneStartTime > 0 && GetTickCount64() - behindSceneStartTime > MARIO_BEHIND_SCENE_TIME)
	{
		behindSceneStartTime = 0;
	}
}

void CMario::ManageAlphaUntouchable()
{
	if (untouchableStartTime > 0) {
		ULONGLONG timePassed = GetTickCount64() - untouchableStartTime;
		if (timePassed > MARIO_UNTOUCHABLE_TIME) {
			untouchableStartTime = 0;
			alpha = 255;
		}
		else
		{
			//if (calculateTime % 2 == 0) alpha = 255
			//per 50ms
			int calculateTime = timePassed / 50 % 2;
			if (calculateTime == 0)
				alpha = 100;
			else alpha = 255;
		}
	}
}

void CMario::PowerReset()
{
	isPower = false;
	powerStartTime = 0;
	PowerDown();
}

void CMario::KickShellAfterHandle()
{
	isHandleShell = false;
	koopaShell->KickByMario();
	koopaShell = NULL;
	state_ = MarioState::kick.GetInstance();
	MarioState::kick.GetInstance()->StartKick();
}

ULONGLONG CalculatePowerTimePassed(int time)
{
	return (GetTickCount64() - time) / MARIO_POWERUP_PER_SECOND;
}

void CMario::PowerControl()
{
	ULONGLONG timePassed;
	if (isPower && powerStartTime > 0)
	{
		timePassed = CalculatePowerTimePassed(powerStartTime);
		if (timePassed < MARIO_MAX_POWER)
		{
			if (power == 0)
				power = timePassed;
			else if (savePower == 0)
			{
				savePower = power;
			}

			if (timePassed <= MARIO_MAX_POWER - savePower) {
				power = savePower + timePassed;
			}
		}
	}
	else if (powerEndTime > 0)
	{
		timePassed = CalculatePowerTimePassed(powerEndTime);
		if (power == 0)
			powerEndTime = 0;
		else if (savePower == 0)
		{
			savePower = power;
		}

		if (savePower - timePassed >= 0) {
			power = savePower - timePassed;
		}
	}	
}

void CMario::LevelUp()
{
	if (level < MARIO_LEVEL_RACCOON)
	{
		y -= MARIO_RACCOON_BBOX_HEIGHT;
		SetLevel(level + 1);
		state_ = MarioState::levelUp.GetInstance();
		MarioState::levelUp.GetInstance()->StartLevelUp();
	}

	Effect* effect = EffectPool::GetInstance()->Create();
	if (effect != NULL)
		effect->InitPoint(EffectPoint::p1000, x, y);
}

void CMario::LevelDown()
{
	if (untouchableStartTime == 0)
	{
		if (level > MARIO_LEVEL_SMALL)
		{
			StartUntouchable();
			y -= MARIO_SMALL_BBOX_HEIGHT;
			state_ = MarioState::levelDown.GetInstance();
			MarioState::levelDown.GetInstance()->StartLevelDown();
		}
		else SetState(MARIO_STATE_DIE);
	}
}

void CMario::HandleInput(Input input)
{
	state_->HandleInput(*this, input);

	state_->Enter(*this);
}

CMario::CMario() : CGameObject()
{
	level = MARIO_LEVEL_SMALL;
	state_ = MarioState::standing.GetInstance();
	nx = 1;
	CGameObject::SetAnimation(MARIO_ANI_SET_ID);
}

void CMario::Render()
{
	int animation = 0;
	int alpha = 255;

	if (GetLevel() == MARIO_LEVEL_RACCOON)
		alpha = 255;
	else alpha = this->alpha;

	if (state == MARIO_STATE_DIE)
		animation = MARIO_ANI_DIE;
	else 
		animation = GetAnimation();
	animation_set->at(animation)->Render(x, y, nx, ny, alpha);
	//RenderBoundingBox();
}

void CMario::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
		case MARIO_STATE_DIE:
		vy = -MARIO_DIE_DEFLECT_SPEED;
		break;
	}
}

void CMario::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	state_->GetBoundingBox(*this, left, top, right, bottom);
}

void CMario::Reset()
{
	state_ = MarioState::standing.GetInstance();
	MarioTailHitState::GetInstance()->tailHitting = false;
	isPower = false;
	isHandleShell = false;
	isUntouchable = false;
	SetLevel(MARIO_LEVEL_SMALL);
	SetSpeed(0, 0);
}

void CMario::SetTail(MarioTail* tail) { this->tail = tail; }