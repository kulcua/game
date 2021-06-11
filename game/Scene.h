#pragma once

#include <d3dx9.h>
#include "KeyEventHandler.h"

class CScene
{
protected:
	CKeyEventHandler* keyHandler;
	int id;
	LPCWSTR sceneFilePath;
	
public:
	CScene(int id, LPCWSTR filePath);
	bool isFinished;
	CKeyEventHandler* GetKeyEventHandler() { return keyHandler; }
	virtual void Load() = 0;
	virtual void Unload() = 0;
	virtual void Update(DWORD dt) = 0;
	virtual void Render() = 0;
	int GetSceneId() { return this->id; }
};

typedef CScene* LPSCENE;

class CSceneKeyHandler : public CKeyEventHandler
{
protected:
	CScene* scene;
public:
	virtual void KeyState(BYTE* state) = 0;
	virtual void OnKeyDown(int KeyCode) = 0;
	virtual void OnKeyUp(int KeyCode) = 0;
	CSceneKeyHandler(CScene* s) :CKeyEventHandler() { scene = s; }
};
