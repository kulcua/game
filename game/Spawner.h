#pragma once
#include "Enermy.h"
class Spawner
{
public:
	virtual ~Spawner() {}
	virtual Enermy* SpawnEnermy() = 0;
};

template <class T>
class SpawnerFor : public Spawner
{
public:
	virtual Enermy* SpawnEnermy() { return new T(); }
};

//Spawner* goombaSpawner = new SpawnerFor<Goomba>();

//public:
//	Spawner(Enermy* prototype)
//		: prototype_(prototype)
//	{}
//
//	Enermy* SpawnEnermy()
//	{
//		return prototype_->Clone();
//	}
//
//private:
//	Enermy* prototype_;
//};

