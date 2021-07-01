#pragma once
#include "GameObject.h"

#define MUSICAL_NOTE_BBOX_SIZE  50
#define MUSICAL_NOTE_ANI_ID 45
#define MUSICAL_NOTE_ANI_WHITE 0
#define MUSICAL_NOTE_ANI_RED 1
#define MUSICAL_NOTE_VY_DEFLECT 0.8f
#define MUSICAL_NOTE_VY_RETURN 0.1f
#define MUSICAL_NOTE_TYPE_WHITE 1
#define MUSICAL_NOTE_TYPE_RED 2

class MusicalNote : public CGameObject
{
	int type;
	float startY;
	float nDeflect;
public:
	bool isHidden;
	MusicalNote(int type, float startY);
	void Deflect(float ny);
	int GetType() { return type; }
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};

