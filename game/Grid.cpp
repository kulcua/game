#include "Grid.h"
#include "GameObject.h"
#include "Game.h"

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
    int cellX = (int)(obj->x / CELL_SIZE_X);
    int cellY = (int)(obj->y / CELL_SIZE_Y);

    // Add to the front of list for the cell it's in.
    obj->prev_ = NULL;
    obj->next_ = cells_[cellX][cellY];
    cells_[cellX][cellY] = obj;

    //DebugOut(L"grid x %d y %d\n", cellX, cellY);

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
    /*CGame::GetInstance()->GetPlayer()->Update(dt, &coObject);
    CGame::GetInstance()->GetCam()->Update(dt, &coObject);*/
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
}

void Grid::GetCell(int& startX, int& startY, int& endX, int& endY)
{
    CCamera* cam = CGame::GetInstance()->GetCam();
    float cx, cy;
    cam->GetPosition(cx, cy);

    startX = (int)(cx / CELL_SIZE_X);
    startY = (int)(cy / CELL_SIZE_Y);
    endX = (int)((cx + CAM_WIDTH) / CELL_SIZE_X);
    endY = (int)((cy + CAM_HEIGHT) / CELL_SIZE_Y);

    //DebugOut(L"GetPosition x %f y %f\n", cx, cy);
    //DebugOut(L"cellStart x %d y %d\n", cellStartX, cellStartY);
    //DebugOut(L"cellEnd x %d y %d\n", cellEndX, cellEndY);
}

//void Grid::HandleMelee()
//{
//    for (int x = 0; x < NUM_CELLS; x++)
//    {
//        for (int y = 0; y < NUM_CELLS; y++)
//        {
//            HandleCell(x, y);
//        }
//    }
//}

//void Grid::HandleCell(int x, int y)
//{
//    CGameObject* obj = cells_[x][y];
//    while (obj != NULL)
//    {
//        // Handle other objs in this cell.
//        HandleObject(obj, obj->next_);
//
//        // Also try the neighboring cells.
//        if (x > 0 && y > 0) HandleObject(obj, cells_[x - 1][y - 1]);
//        if (x > 0) HandleObject(obj, cells_[x - 1][y]);
//        if (y > 0) HandleObject(obj, cells_[x][y - 1]);
//        if (x > 0 && y < NUM_CELLS - 1)
//        {
//            HandleObject(obj, cells_[x - 1][y + 1]);
//        }
//
//        obj = obj->next_;
//    }
//}

void Grid::Move(CGameObject* obj, double x, double y)
{
    // NOTE: Move() will set x, y though it has been set on Update()
    // See which cell it was in.
    int oldCellX = (int)(obj->x / CELL_SIZE_X);
    int oldCellY = (int)(obj->y / CELL_SIZE_Y);

    // See which cell it's moving to.
    int cellX = (int)(x / CELL_SIZE_X);
    int cellY = (int)(y / CELL_SIZE_Y);

    obj->x = x;
    obj->y = y;

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
//
//void Grid::HandleObject(CGameObject* obj, CGameObject* other)
//{
//    while (other != NULL)
//    {
//       /* if (distance(obj, other) < ATTACK_DISTANCE)
//        {
//            handleAttack(obj, other);
//        }*/
//
//        other = other->next_;
//    }
//}