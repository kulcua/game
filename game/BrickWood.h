#pragma once
#include "GameObject.h"
#include "PowerUpItem.h"

#define BRICK_WOOD_BBOX_SIZE  48
#define BRICK_WOOD_ANI_ID  43
#define BRICK_WOOD_ANI_WOOD 0
#define BRICK_WOOD_ANI_DISABLE 1
#define BRICK_WOOD_VX_DEFLECT 0.5f
#define BRICK_WOOD_VX_RETURN 0.1f
#define BRICK_WOOD_DEFLECT_MARIO_VX 0.1f

class BrickWood : public CGameObject
{
	friend class CMario;
	int type;
	float startX;
	float nDeflect;
	CMario* mario;
	PowerUpItem* item;
	bool throwItem;
public:
	BrickWood(float startX);
	void SetItem(PowerUpItem* item) { this->item = item; }
	void Deflect(float nx);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};


