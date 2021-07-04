#include "MusicalNote.h"
#include "Utils.h"
#include "Mario.h"
#include "Game.h"

MusicalNote::MusicalNote(int type, float startY)
{
	SetAnimation(MUSICAL_NOTE_ANI_ID);
	this->type = type;
	if (type == 1)
		isHidden = false;
	else isHidden = true;
	this->startY = startY;
}

void MusicalNote::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	y += dy;
	if ((y < startY && nDeflect > 0) || (y > startY && nDeflect < 0)) // take to start_y after deflect cause disable
	{
		vy = nDeflect * MUSICAL_NOTE_VY_RETURN;
	}
	else
	{
		y = startY;
		vy = 0;
		nDeflect = 0;
	}
}

void MusicalNote::Deflect(float ny)
{
	if (nDeflect == 0)
	{
		nDeflect = ny;
		this->vy = -nDeflect * MUSICAL_NOTE_VY_DEFLECT;
	}
}

void MusicalNote::Render()
{
	if (isHidden == false)
	{
		int ani = 0;
		if (type == MUSICAL_NOTE_TYPE_WHITE)
			ani = MUSICAL_NOTE_ANI_WHITE;
		else ani = MUSICAL_NOTE_ANI_RED;
		animation_set->at(ani)->Render(x, y, nx, ny);
	}	
}

void MusicalNote::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + MUSICAL_NOTE_BBOX_SIZE;
	b = y + MUSICAL_NOTE_BBOX_SIZE;
}