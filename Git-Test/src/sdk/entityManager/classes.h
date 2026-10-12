#pragma once
#include "../math/math.h"
#include "../mem/offsets.h"

#define SCHEMA(type, name, offset) \
    type& name() { \
        return *reinterpret_cast<type*>(reinterpret_cast<uintptr_t>(this) + offset); \
    } \
    const type& name() const { \
        return *reinterpret_cast<const type*>(reinterpret_cast<uintptr_t>(this) + offset); \
    }

class Player
{
public:
    SCHEMA(int, health, offs::Health);
    SCHEMA(int, armor, offs::Armor);
    SCHEMA(Vector3, pos, offs::Pos);
    SCHEMA(Vector3, headPos, offs::HeadPos);
    SCHEMA(Vector3, viewAng, offs::ViewAng);
    SCHEMA(int, isAlive, offs::IsAlive)
};