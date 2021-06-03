#include "Portal.h"
#include "PortalManager.h"
#define PORT_HELP_ANI_ID 2
#define PORT_HELP_ALIGN 50

//CPortal::CPortal(float l, float t, float r, float b, int scene_id)
//{
//	this->scene_id = scene_id;
//	x = l;
//	y = t;
//	width = r - l + 1;
//	height = b - t + 1;
//}

CPortal::CPortal(string type)
{
	this->type = type;
	if (type.compare("node") == 0)
		scene_id = 0;
	else if (type.compare("boss-castle") == 0)
		SetAnimation(PORT_HELP_ANI_ID);
	else this->scene_id = PortalManager::GetInstance()->portScene[type];
}

void CPortal::Render()
{
	if (type.compare("boss-castle") == 0)
	{
		//render help
		animation_set->at(0)->Render(x + PORT_HELP_ALIGN, y - PORT_HELP_ALIGN, nx, ny, 255);
	}
	else {
		int spriteId = PortalManager::GetInstance()->portSprite[type];
		spriteId = PortalManager::GetInstance()->portSprite[type];
		CSprites::GetInstance()->Get(spriteId)->Draw(x, y, -1, -1);
	}
	//RenderBoundingBox();
}

void CPortal::GetBoundingBox(float& l, float &t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + PORTAL_WIDTH;
	b = y + PORTAL_HEIGHT;
}