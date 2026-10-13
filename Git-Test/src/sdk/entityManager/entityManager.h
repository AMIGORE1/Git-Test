#pragma once
#include <vector>
#include <shared_mutex>
#include "../math/math.h"
#include "../mem/mem.h"
#include "../mem/offsets.h"
#include "classes.h"

/*struct Entity{
	Vector3 headPos;
	Vector3 pos;

	int health;
	int team;
	bool isAlive;

};



class EntityManager
{
	std::vector<Entity> entities;
	Player* localPlayer = nullptr;
	uintptr_t entityListAddrs = 0;
	uintptr_t base = 0;
	std::shared_mutex mutex;
	EntityManager();
public:
	static EntityManager& Get();
	void Update();
	const std::vector<Entity>& GetEntities();
	Player* GetLocalPlayer();
};*/


struct Entity {
	Vector3 headPos;
	Vector3 pos;
	int health;
	int armor;
	int team;
	bool isAlive;
};

class EntityManager {
	std::vector<Entity> entities;
	Player* player = nullptr;
	uintptr_t entityListAddr = 0;
	uintptr_t base = 0;
	std::shared_mutex mutex;
	EntityManager();
public:
	static EntityManager& Get();
	const std::vector<Entity>& GetEntities();
	Player* GetPlayer();
	void Update();
};