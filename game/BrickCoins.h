#pragma once
#include "Brick.h"
#define BRICK_STATE_THROW_ITEM 100
#define BRICK_STATE_NUM_COINS 10

class BrickCoins : public CBrick
{
	CItem* item;
	int type;
	int numItem = BRICK_STATE_NUM_COINS;
	vector<CItem*> items;
public:
	float start_y;
	BrickCoins(int type, float x, float y);
	int GetType() { return type; }
	void SetListItems(vector<CItem*> items) { this->items = items; }
	virtual void SetState(int state);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
};
