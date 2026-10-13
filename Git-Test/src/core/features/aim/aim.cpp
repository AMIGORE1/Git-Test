#include "aim.h"

void Aim::Update() {
    auto targetOpt = GetClosest();
    if (!targetOpt) return;

    AimBot(&(*targetOpt));
}

std::optional<Entity> Aim::GetClosest() {
    auto& em = EntityManager::Get();
    auto locP = em.GetPlayer();
    if (!locP) return std::nullopt; 

    std::optional<Entity> closestEntity = std::nullopt;
    float closestDist = 999999.0f;

    for (const auto& ent : em.GetEntities()) {
        if (ent.isAlive) continue;
        if (ent.team == locP->team()) continue;

        float dist = Vector3::distance(locP->headPos(), ent.headPos);
        if (dist < closestDist) {
            closestDist = dist;
            closestEntity = ent; 
        }
    }
    return closestEntity;
}

void Aim::AimBot(Entity* target) {

    if (!(GetAsyncKeyState(VK_RBUTTON) & 0x8000))
        return;
   
    Player* pl = EntityManager::Get().GetPlayer();
    Vector3 enemyHead = target->headPos;
    enemyHead.z += 0.3f; 

    Vector3 delta = enemyHead - pl->headPos();
    float distance = sqrt(delta.x * delta.x + delta.y * delta.y);

    float yaw = atan2(delta.y, delta.x) * (180.0f / M_PI) + 90.0f;
    float pitch = atan2(delta.z, distance) * (180.0f / M_PI);

    pl->viewAng().x = yaw;  
    pl->viewAng().y = pitch; 
}