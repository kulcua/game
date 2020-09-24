#include "Item.h"
#include "Utils.h"

//void CItem::Update(ItemType type)
//{
//	vy += ITEM_GRAVITY * dt;
//	switch (type)
//	{
//	case COIN:
//	{
//		if (true)
//		{
//			vy = -ITEM_COIN_JUMP_SPEED;
//		}
//	}
//		break;
//	case LEAF:
//
//		break;
//	}
//}

void CItem::Render()
{
	//int ani;
	//if state brick truyen vo la gi thi render item state do
	animation_set->at(0)->Render(x, y, NULL);
	DebugOut(L"item");
	//RenderBoundingBox();
}

void CItem::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + ITEM_BBOX_WIDTH;
	b = y + ITEM_BBOX_HEIGHT;
}