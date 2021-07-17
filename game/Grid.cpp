#include "Grid.h"
#include "GameObject.h"
#include "Game.h"
#include "HUD.h"
#include "Enermy.h"
#include "EffectPool.h"
#include "BoomerangPool.h"
#include "FireBallPool.h"
#include "MiniGoombaPool.h"

Grid::Grid() {
    for (int x = 0; x < NUM_CELLS; x++)
    {
        for (int y = 0; y < NUM_CELLS; y++)
        {
            cells_[x][y] = new Cell();
        }
    }
}

void Grid::Add(CGameObject* obj, int id)
{
    int cellStartX;
    int cellStartY;
    int cellEndX;
    int cellEndY;

    if (objectCells.find(id) == objectCells.end())
    {
        // not found
        cellStartX = 0;
        cellStartY = 0;
        cellEndX = 0;
        cellEndY = 0;
    }
    else {
        D3DXVECTOR4 cellNumber = objectCells[id];
        cellStartX = (int)cellNumber[0];
        cellStartY = (int)cellNumber[1];
        cellEndX = (int)cellNumber[2];
        cellEndY = (int)cellNumber[3];
    }
  
    for (int i = cellStartX; i < cellEndX + 1; i++)
    {
        for (int j = cellStartY; j < cellEndY + 1; j++)
        {
            cells_[i][j]->AddObject(obj);
        }
    }
}

void Grid::Update(DWORD dt)
{
    vector<LPGAMEOBJECT> coObject;

    int cellStartX, cellStartY, cellEndX, cellEndY;
    GetCell(cellStartX, cellStartY, cellEndX, cellEndY);

    for (int i = cellStartX; i < cellEndX; i++)
    {
        for (int j = cellStartY; j < cellEndY; j++)
        {
            vector<CGameObject*> objList = cells_[i][j]->GetListObjects();
            for (int i = 0; i < objList.size(); i++)
            {
                if (objList[i]->die == false)
                {
                    coObject.push_back(objList[i]);
                }
            }
        }
    }

    EffectPool::GetInstance()->Update(dt, &coObject);
    BoomerangPool::GetInstance()->Update(dt, &coObject);
    FireBallPool::GetInstance()->Update(dt, &coObject);
    MiniGoombaPool::GetInstance()->Update(dt, &coObject);

    for (int i = cellStartX; i < cellEndX; i++)
    {
        for (int j = cellStartY; j < cellEndY; j++)
        {
            cells_[i][j]->Update(dt, coObject);
        }
    }

    CGame::GetInstance()->GetCam()->Update(dt, &coObject);
    // check null to avoid error when Unload() delete all list objects
    CGame::GetInstance()->GetCurrentScene()->GetPlayer()->Update(dt, &coObject);
    HUD* hud = CGame::GetInstance()->GetCurrentScene()->GetHUD();
    if (hud != NULL)
        hud->Update(dt, &coObject);
}

void Grid::Render()
{
    int cellStartX, cellStartY, cellEndX, cellEndY;
    GetCell(cellStartX, cellStartY, cellEndX, cellEndY);

    for (int i = cellStartX; i < cellEndX; i++)
    {
        for (int j = cellStartY; j < cellEndY; j++)
        {
            cells_[i][j]->Render();
        }
    }

    EffectPool::GetInstance()->Render();
    BoomerangPool::GetInstance()->Render();
    FireBallPool::GetInstance()->Render();
    MiniGoombaPool::GetInstance()->Render();
}

void Grid::GetCell(int& startX, int& startY, int& endX, int& endY)
{
    CCamera* cam = CGame::GetInstance()->GetCam();
    float cx, cy;
    cam->GetPosition(cx, cy);

    startX = (int)(cx / CELL_SIZE);
    startY = (int)(cy / CELL_SIZE);
    endX = (int)((cx + CAM_WIDTH) / CELL_SIZE) + 1;
    endY = (int)((cy + CAM_HEIGHT) / CELL_SIZE) + 1;

    //DebugOut(L"%d %d %d %d\n", startX, startY, endX, endY);
}

void Grid::Move(CGameObject* obj, float x, float y)
{
    int oldCellX = (int)(obj->oldX / CELL_SIZE);
    int oldCellY = (int)(obj->oldY / CELL_SIZE);

    // See which cell it's moving to.
    int cellX = (int)(x / CELL_SIZE);
    int cellY = (int)(y / CELL_SIZE);

    // If it didn't change cells, we're done.
    if (oldCellX == cellX && oldCellY == cellY) return;

    cells_[oldCellX][oldCellY]->RemoveObject(obj);
    cells_[cellX][cellY]->AddObject(obj);
}

void Grid::ReadGridData(const char* filePath)
{
    TiXmlDocument doc(filePath);
    if (!doc.LoadFile())
    {
        return;
    }
    TiXmlElement* root = doc.RootElement();
    TiXmlElement* element = root->FirstChildElement(); // config
    element = element->NextSiblingElement(); // data
    TiXmlElement* objectGroup = element->FirstChildElement(); //group obj

    while (objectGroup)
    {
        element = objectGroup->FirstChildElement(); //id - cell number xy
        while (element)
        {
            int objectId, cellX, cellY, endX, endY;
            string cellEndX, cellEndY; // avoid NaN cases when obj doesn't have width, height
            element->QueryIntAttribute("id", &objectId);
            element->QueryIntAttribute("cellx", &cellX);
            element->QueryIntAttribute("celly", &cellY);
            cellEndX = element->Attribute("xEnd");
            cellEndY = element->Attribute("yEnd");
            if (cellEndX.compare("NaN") == 0 && cellEndY.compare("NaN") == 0)
            {
                endX = cellX;
                endY = cellY;
            }
            else {
                endX = atoi(cellEndX.c_str());
                endY = atoi(cellEndY.c_str());
            }
            //DebugOut(L"%d %d %d %d\n", cellX, cellY, endX, endY);
            objectCells[objectId] = D3DXVECTOR4(cellX, cellY, endX, endY);

            element = element->NextSiblingElement();
        }
        objectGroup = objectGroup->NextSiblingElement();
    }
}

Grid::~Grid()
{
    for (int x = 0; x < NUM_CELLS; x++)
    {
        for (int y = 0; y < NUM_CELLS; y++)
        {
            delete cells_[x][y];
        }
    }
}
