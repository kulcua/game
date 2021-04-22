#pragma once
#include "Item.h"
#define RED_MUSHROOM_ANI_ID 26
#define LEAF_ANI_ID 27

class PowerUpItem : public CItem
{
	friend class CMario;
	CMario* mario;
	int ani = 0;
	float startY;
	bool outBrick;
	void UpdateMushroom(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void UpdateLeaf(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
public:
	PowerUpItem();  
	void SetAnimation(int ani);
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
};

