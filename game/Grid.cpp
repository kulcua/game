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
    // Clear the grid.
    for (int x = 0; x < NUM_CELLS; x++)
    {
        for (int y = 0; y < NUM_CELLS; y++)
        {
            cells_[x][y] = NULL;
        }
    }
}

void Grid::Add(CGameObject* obj)
{
    // Determine which grid cell it's in.
    int cellX = (int)(obj->x / CELL_SIZE);
    int cellY = (int)(obj->y / CELL_SIZE);

    // Add to the front of list for the cell it's in.
    obj->prev_ = NULL;
    obj->next_ = cells_[cellX][cellY];
    cells_[cellX][cellY] = obj;

    if (obj->next_ != NULL)
    {
        obj->next_->prev_ = obj;
    }
}

void Grid::Add(CGameObject* obj, int id)
{
    D3DXVECTOR2 cellNumber = objectCells[id];
    int cellX = (int)cellNumber.x;
    int cellY = (int)cellNumber.y;
    // Add to the front of list for the cell it's in.
    obj->prev_ = NULL;
    obj->next_ = cells_[cellX][cellY];
    cells_[cellX][cellY] = obj;

    if (obj->next_ != NULL)
    {
        obj->next_->prev_ = obj;
    }
}

void Grid::Update(DWORD dt)
{
    vector<LPGAMEOBJECT> coObject;

    int cellStartX, cellStartY, cellEndX, cellEndY;
    GetCell(cellStartX, cellStartY, cellEndX, cellEndY);

    for (int i = cellStartX; i < cellEndX + 1; i++)
    {
        for (int j = cellStartY; j < cellEndY + 1; j++)
        {
            CGameObject* obj = cells_[i][j];
       
            while (obj != NULL)
            {
                if (obj->die == false)
                {
                    coObject.push_back(obj);
                }
                obj = obj->next_;
            }
        }
    }

    EffectPool::GetInstance()->Update(dt, &coObject);
    BoomerangPool::GetInstance()->Update(dt, &coObject);
    FireBallPool::GetInstance()->Update(dt, &coObject);
    MiniGoombaPool::GetInstance()->Update(dt, &coObject);

    for (int i = cellStartX; i < cellEndX + 1; i++)
    {
        for (int j = cellStartY; j < cellEndY + 1; j++)
        {
            CGameObject* obj = cells_[i][j];
            while (obj != NULL)
            {
                if (obj->die == false)
                {
                    obj->Update(dt, &coObject);
                }
                obj = obj->next_;
            }
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

    for (int i = cellStartX; i < cellEndX + 1; i++)
    {
        for (int j = cellStartY; j < cellEndY + 1; j++)
        {
            CGameObject* obj = cells_[i][j];
            while (obj != NULL)
            {
                if (obj->die == false)
                    obj->Render();
                obj = obj->next_;
            }
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

    // Unlink it from the list of its old cell.
    if (obj->prev_ != NULL)
    {
        obj->prev_->next_ = obj->next_;
    }

    if (obj->next_ != NULL)
    {
        obj->next_->prev_ = obj->prev_;
    }
    
    // If it's the head of a list, remove it.
    if (cells_[oldCellX][oldCellY] == obj)
    {
        cells_[oldCellX][oldCellY] = obj->next_;
    }
    // Add it back to the grid at its new cell.
    Add(obj);
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
            int objectId, cellX, cellY;
            element->QueryIntAttribute("id", &objectId);
            element->QueryIntAttribute("cellx", &cellX);
            element->QueryIntAttribute("celly", &cellY);
            objectCells[objectId] = D3DXVECTOR2(cellX, cellY);

            element = element->NextSiblingElement();
        }
        objectGroup = objectGroup->NextSiblingElement();
    }
}