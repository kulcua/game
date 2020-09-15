#include "Maps.h"
#include "fstream"
#include "Textures.h"
#include "Sprites.h"

using namespace std;

CMaps* CMaps::__instance = NULL;

CMaps* CMaps::GetInstance()
{
	if (__instance == NULL) __instance = new CMaps();
	return __instance;
}

void CMaps::Add(int id, LPCWSTR path_img, int width, int height,
	int num_tile_x, int num_tile_y, LPCWSTR path_txt, D3DCOLOR transparentColor)
{
	//doc tung so tile trong file txt va luu mang
	ifstream inp(path_txt, ios::in);
	max_map_x = width / TILE_SIZE;
	max_map_y = height / TILE_SIZE;

	this->num_tile_x = num_tile_x;
	this->num_tile_y = num_tile_y;

	for (int i = 0; i < num_tile_y; i++)
		for (int j = 0; j < num_tile_x; j++)
		{
			inp >> tile[i][j];
		}
	inp.close();

	//add vao textures nguyen hinh tileset
	CTextures::GetInstance()->Add(id, path_img, transparentColor);
	//lay ra lai tu textures nguyen hinh tileset
	LPDIRECT3DTEXTURE9 texMap = CTextures::GetInstance()->Get(id);
 
	int id_sprite = 0; //khoi tao gia tri dau tien theo file txt
	//lay theo tung tile add vao sprite x64
	for (int i = 0; i < max_map_y; i++) //7
	{
		for (int j = 0; j < max_map_x; j++) //20
		{
			CSprites::GetInstance()->Add(id_sprite, TILE_SIZE * j, TILE_SIZE * i, TILE_SIZE * (j + 1), TILE_SIZE * (i + 1), texMap);
			id_sprite++;
		}
	}		
}

void CMaps::Render()
{
	for (int i = 0; i < num_tile_y; i++)
		for (int j = 0; j < num_tile_x; j++)
		{
			CSprites::GetInstance()->Get(tile[i][j])->Draw(j * TILE_SIZE, i * TILE_SIZE, NULL);
		}
}

