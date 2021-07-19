#include <d3dx9.h>
#include <algorithm>
#include "Utils.h"
#include "Game.h"
#include "GameObject.h"
#include "Sprites.h"
#include "Grid.h"
#include "Textures.h"
#include "Coin.h"
#include "BrickBlock.h"
#include "KoopaBound.h"
#include "BrotherBound.h"
#include "MusicalNote.h"

CGameObject::CGameObject()
{
	x = y = 0;
	vx = vy = 0;
}

void CGameObject::SetGrid(Grid* grid, int id)
{
	grid_ = grid;
	grid_->Add(this, id);
}

void CGameObject::SetAnimation(int ani)
{
	CAnimationSets* animation_sets = CAnimationSets::GetInstance();
	LPANIMATION_SET ani_set = animation_sets->Get(ani);
	SetAnimationSet(ani_set);
}

void CGameObject::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	this->dt = dt;
	dx = vx * dt;
	dy = vy * dt;
	oldX = x;
	oldY = y;
}

bool CGameObject::AABB(CGameObject *obj)
{
	float al, at, ar, ab;
	this->GetBoundingBox(al, at, ar, ab);

	float bl, bt, br, bb;
	obj->GetBoundingBox(bl, bt, br, bb);

	return !(ar < bl || al > br || at > bb || ab < bt);
}

//Extension of original SweptAABB to deal with two moving objects
LPCOLLISIONEVENT CGameObject::SweptAABBEx(LPGAMEOBJECT coO)
{
	float sl, st, sr, sb;		// static object bbox
	float ml, mt, mr, mb;		// moving object bbox
	float t, nx, ny;

	coO->GetBoundingBox(sl, st, sr, sb);

	//deal with moving object: m speed = original m speed - collide object speed
	float svx, svy;
	coO->GetSpeed(svx, svy);

	float sdx = svx * dt;
	float sdy = svy * dt;

	// (rdx, rdy) is RELATIVE movement distance/velocity 
	float rdx = this->dx - sdx;
	float rdy = this->dy - sdy;

	GetBoundingBox(ml, mt, mr, mb);

	CGame::SweptAABB(
		ml, mt, mr, mb,
		rdx, rdy,
		sl, st, sr, sb,
		t, nx, ny
	);

	CCollisonEvent* e = new CCollisonEvent(t, nx, ny, rdx, rdy,coO);

	return e;
}

/*
	Calculate potential collisions with the list of colliable objects

	coObjects: the list of colliable objects
	coEvents: list of potential collisions
*/
void CGameObject::CalcPotentialCollisions(
	vector<LPGAMEOBJECT>* coObjects,
	vector<LPCOLLISIONEVENT>& coEvents)
{
	for (UINT i = 0; i < coObjects->size(); i++)
	{
		LPCOLLISIONEVENT e = SweptAABBEx(coObjects->at(i));

		if (e->t > 0 && e->t <= 1.0f)
			coEvents.push_back(e);
		else
			delete e;
	}

	std::sort(coEvents.begin(), coEvents.end(), CCollisonEvent::compare);
}

void CheckCollisionWithItem(bool& skipBlockX, bool& skipBlockY, CGameObject* obj_x, CGameObject* obj_y)
{
	if (dynamic_cast<Coin*>(obj_x) || dynamic_cast<CItem*>(obj_x))
	{
		skipBlockX = true;
	}
	if (dynamic_cast<Coin*>(obj_y) || dynamic_cast<CItem*>(obj_y)
		|| dynamic_cast<KoopaBound*>(obj_y) || dynamic_cast<BrotherBound*>(obj_y))
	{
		skipBlockY = true;
	}
	if (dynamic_cast<BrickBlock*>(obj_x))
	{
		BrickBlock* brickBlock = dynamic_cast<BrickBlock*>(obj_x);
		if (brickBlock->isCoin)
			skipBlockX = true;
	}
	if (dynamic_cast<BrickBlock*>(obj_y))
	{
		BrickBlock* brickBlock = dynamic_cast<BrickBlock*>(obj_y);
		if (brickBlock->isCoin)
			skipBlockY = true;
	}
	if (dynamic_cast<MusicalNote*>(obj_x))
	{
		MusicalNote* note = dynamic_cast<MusicalNote*>(obj_x);
		if (note->isHidden)
		{
			skipBlockX = true;
		}
	}
}

void CGameObject::FilterCollision(
	vector<LPCOLLISIONEVENT>& coEvents,
	vector<LPCOLLISIONEVENT>& coEventResult,
	float& nx, float& ny)
{
	float min_tx = 1.0f;
	float min_ty = 1.0f;
	int min_ix = -1;
	int min_iy = -1;
	float rdx = 0;
	float rdy = 0;

	nx = 0.0f;
	ny = 0.0f;

	CGameObject* obj_y = NULL, * obj_x = NULL;

	coEventResult.clear();

	for (UINT i = 0; i < coEvents.size(); i++)
	{
		LPCOLLISIONEVENT c = coEvents[i];

		if (c->t < min_ty && c->ny != 0)
		{
			min_ty = c->t;
			ny = c->ny;
			min_iy = i;
			rdy = c->dy;
			obj_y = c->obj;
		}

		if (c->t < min_tx && c->nx != 0)
		{
			min_tx = c->t;
			nx = c->nx;
			min_ix = i;
			rdx = c->dx;
			obj_x = c->obj;
		}
	}

	// skip collision if obj isOnGround with A and collise nx with A
	if (obj_x != NULL && obj_y != NULL && obj_x->y == obj_y->y)
	{
		min_tx = 1;
		nx = 0;
	}
	else if (min_ix >= 0) coEventResult.push_back(coEvents[min_ix]);

	if (min_iy >= 0) coEventResult.push_back(coEvents[min_iy]);

	// do not block obj when collision with item
	bool skipBlockX = false, skipBlockY = false;
	CheckCollisionWithItem(skipBlockX, skipBlockY, obj_x, obj_y);

	if (skipBlockX == false)
	{
		x += min_tx * dx + nx * 0.4f;
		if (nx != 0) vx = 0;
	}
	
	if (skipBlockY == false)
	{
		if (isOnGround == false)
			y += min_ty * dy + ny * 0.4f;
		if (ny != 0) vy = 0;
	}
}

void CGameObject::RenderBoundingBox()
{
	D3DXVECTOR3 p(x, y, 0);
	RECT rect;

	LPDIRECT3DTEXTURE9 bbox = CTextures::GetInstance()->Get(ID_TEX_BBOX);

	float l, t, r, b;

	GetBoundingBox(l, t, r, b);
	rect.left = 0;
	rect.top = 0;
	rect.right = (int)r - (int)l;
	rect.bottom = (int)b - (int)t;

	CGame::GetInstance()->Draw(x, y, nx, ny, bbox, rect.left, rect.top, rect.right, rect.bottom, 32);
}

CGameObject::~CGameObject()
{

}