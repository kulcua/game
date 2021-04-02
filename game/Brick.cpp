#include "Brick.h"
#include "Utils.h"

CBrick::CBrick(float x, float y, string name)
{
	this->x = x;
	this->y = y;
	start_y = y;
	this->name = name;
	//this->typeItem = type;
	SetAnimation(BRICK_ANI_ID);
}

void CBrick::SetAnimation(int ani)
{
	CAnimationSets* animation_sets = CAnimationSets::GetInstance();
	LPANIMATION_SET ani_set = animation_sets->Get(ani);
	SetAnimationSet(ani_set);
}

void CBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);

	y += dy;

	//if (brick->GetState() == BRICK_STATE_DISABLE && !brick->dropItem)
	//{
	//	brick->dropItem = true;
	//	CAnimationSets* animation_sets = CAnimationSets::GetInstance();
	//	int type = brick->GetTypeItem();
	//	if (type == ITEM_STATE_RED_MUSHROOM) //check neu item set theo level 1
	//	{
	//		type += player->GetLevel() - 1; //-1 de lay level mario can upgrade theo item
	//		if (type > ITEM_STATE_LEVEL_MAX)
	//			type = ITEM_STATE_LEVEL_MAX;
	//	}
	//	CItem* item = new CItem(type, player);
	//	item->SetPosition(brick->x, brick->y);
	//	LPANIMATION_SET ani_set = animation_sets->Get(type);
	//	item->SetAnimationSet(ani_set);
	//	objects.insert(objects.begin() + i, item);
	//}
	if (GetState() == BRICK_STATE_DISABLE)
	{
		if (y < start_y) // take brick to start_y after deflect cause disable
		{
			vy = BRICK_RETURN_START_POS_VY;
		}
		else
		{
			y = start_y;
		}

		if (dropItem == false)
		{
			dropItem = true;
		}
	}	
}

void CBrick::Render()
{
	int ani;
	if (state == BRICK_STATE_DISABLE)
	{
		ani = BRICK_ANI_DISABLE;
	}	
	else
	{
		ani = BRICK_ANI_ENABLE;
	}
	animation_set->at(ani)->Render(x, y, NULL);
	//RenderBoundingBox();
}

void CBrick::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case BRICK_STATE_DISABLE:
		vy -= BRICK_JUMP_DEFLECT_Y;
		break;
	default:
		break;
	}
}

void CBrick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + BRICK_BBOX_WIDTH;
	b = y + BRICK_BBOX_HEIGHT;
}