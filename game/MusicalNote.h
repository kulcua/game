#pragma once
#include "GameObject.h"

#define MUSICAL_NOTE_BBOX_SIZE  50
#define MUSICAL_NOTE_ANI_ID 45
#define MUSICAL_NOTE_ANI_WHITE 0
#define MUSICAL_NOTE_ANI_RED 1
#define MUSICAL_NOTE_VY_DEFLECT 0.5f
#define MUSICAL_NOTE_VY_RETURN 0.1f
#define MUSICAL_NOTE_TYPE_WHITE 1
#define MUSICAL_NOTE_TYPE_RED 2
#define MUSICAL_NOTE_SWITCH_PORT_TIME 400
#define MUSICAL_NOTE_DEFLECT_MARIO_DEFAULT 0.5f
#define MUSICAL_NOTE_DEFLECT_MARIO_WHITE 1.2f
#define MUSICAL_NOTE_DEFLECT_MARIO_RED 1.5f

class MusicalNote : public CGameObject
{
	friend class CMario;
	int type;
	float startY;
	float nDeflect;
	CMario* mario;
	int portIn = 0;
	ULONGLONG switchPortTimeStart;
public:
	bool isHidden;
	MusicalNote(int type, float startY);
	void Deflect(float ny);
	void SetPortIn(int port) { this->portIn = port; }
	int GetType() { return type; }
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	void StartSwitchPort() { switchPortTimeStart = GetTickCount64(); }
};

