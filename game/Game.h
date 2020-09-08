#pragma once
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <unordered_map>
#include <dinput.h>

#include "PlayScene.h"
#include "Scene.h"

using namespace std;

#define DIRECTINPUT_VERSION 0x0800

#define KEYBOARD_BUFFER_SIZE 1024

#define MAX_GAME_LINE 1024

#define GAME_FILE_SECTION_UNKNOWN -1
#define GAME_FILE_SECTION_SETTINGS 1
#define GAME_FILE_SECTION_SCENES 2

//Abstract class to define keyboard event handlers
//class CKeyEventHandler
//{
//public:
//	virtual void KeyState(BYTE* state) = 0;
//	virtual void OnKeyDown(int KeyCode) = 0;
//	virtual void OnKeyUp(int KeyCode) = 0;
//};
//
//typedef CKeyEventHandler* LPKEYEVENTHANDLER;

class CGame {
	static CGame* __instance;
	HWND hWnd;	// Window handle

	LPDIRECT3D9 d3d = NULL;	// Direct3D handle
	LPDIRECT3DDEVICE9 d3ddv = NULL;	// Direct3D device object

	LPDIRECT3DSURFACE9 backBuffer = NULL;
	LPD3DXSPRITE spriteHandler = NULL;	// Sprite helper library to help us draw 2D image on the screen 

	LPDIRECTINPUT8 di;	// The DirectInput object 
	LPDIRECTINPUTDEVICE8 didv;	// The keyboard device 

	BYTE keyStates[256];	// DirectInput keyboard state buffer 
	DIDEVICEOBJECTDATA keyEvents[KEYBOARD_BUFFER_SIZE];	// Buffered keyboard data

	LPKEYEVENTHANDLER keyHandler;

	float cam_x = 0.0f;
	float cam_y = 0.0f;

	int screen_width;
	int screen_height;

	unordered_map<int, LPSCENE> scenes;
	int current_scene;

	void _ParseSection_SETTINGS(string line);
	void _ParseSection_SCENES(string line);

public:
	void InitKeyBoard();
	void SetKeyHandler(LPKEYEVENTHANDLER handler) { keyHandler = handler; }
	void Init(HWND hWnd);
	void Draw(float x, float y, LPDIRECT3DTEXTURE9 texture, int left, int top, int right, int bottom, int alpha = 255);

	int IsKeyDown(int KeyCode);
	void ProcessKeyBoard();

	void Load(LPCWSTR gameFile);
	LPSCENE GetCurrentScene() { return scenes[current_scene]; }
	void SwitchScene(int scene_id);

	int GetScreenWidth() { return screen_width; }
	int GetScreenHeight() { return screen_height; }

	static void SweptAABB(
		float ml,
		float mt,
		float mr,
		float mb,
		float dx,
		float dy,
		float sl,
		float st,
		float sr,
		float sb,
		float& t,
		float& nx,
		float& ny);

	LPDIRECT3DDEVICE9 GetDirect3DDevice() { return this->d3ddv; }
	LPDIRECT3DSURFACE9 GetBackBuffer() { return this->backBuffer; }
	LPD3DXSPRITE GetSpriteHandler() { return this->spriteHandler; }

	void SetCamPos(float x, float y) { cam_x = x; cam_y = y; }

	static CGame* GetInstance();

	~CGame();
};

