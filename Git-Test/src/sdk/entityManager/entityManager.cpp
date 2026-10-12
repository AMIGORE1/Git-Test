#include "entityManager.h"

EntityManager::EntityManager() {
    base = Mem::GetModuleBase("ac_client.exe");
}

EntityManager& EntityManager::Get()
{
    static EntityManager instance;
    return instance;
}

void EntityManager::Update()
{
    if (!entityListAddrs)
        entityListAddrs = *reinterpret_cast<uintptr_t*>(base + offs::EntityList);
    if (!entityListAddrs) return;

    uintptr_t localPlayerPtr = *reinterpret_cast<uintptr_t*>(base + offs::LocalPlayer);
    if (!localPlayerPtr) return;

    Player* localPlayer = reinterpret_cast<Player*>(localPlayerPtr);

    if (localPlayer->health() <= 0 || localPlayer->health() > 100)
        return;

    int numPlayers = *reinterpret_cast<int*>(base + offs::NumOfPlayers);
    if (numPlayers <= 1 || numPlayers > 32)
        return;

    Entity** entityList = reinterpret_cast<Entity**>(entityListAddrs);
    std::vector<Entity> temp;
    temp.reserve(32);

    for (int i = 1; i < numPlayers; i++)
    {
        Entity* currEnt = entityList[i];

        if (!currEnt) continue;
            
        if (currEnt == reinterpret_cast<Entity*>(localPlayerPtr)) continue;

        Entity ent{};
        ent.health = *reinterpret_cast<int*>(
            reinterpret_cast<uintptr_t>(currEnt) + offs::Health);
        ent.pos = *reinterpret_cast<Vector3*>(
            reinterpret_cast<uintptr_t>(currEnt) + offs::Pos);
        ent.headPos = *reinterpret_cast<Vector3*>(
            reinterpret_cast<uintptr_t>(currEnt) + offs::HeadPos);
        ent.isAlive = *reinterpret_cast<bool*>(
            reinterpret_cast<uintptr_t>(currEnt) + offs::IsAlive);

        temp.push_back(ent);
    }

    {
        std::unique_lock lock(mutex);
        entities.swap(temp);
        this->localPlayer = localPlayer;
    }
}

Player* EntityManager::GetLocalPlayer() {
    std::shared_lock lock(mutex);
    return localPlayer;
}

const std::vector<Entity>& EntityManager::GetEntities()
{
    std::shared_lock lock(mutex);
    return entities;
}