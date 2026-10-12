#pragma once
#include <Windows.h>
#include <optional>
#include "../../../sdk/entityManager/entityManager.h"
#include "../../../sdk/entityManager/classes.h"
#include "../../../../ext/imgui/imgui.h"
namespace Aim
{
	void Update();
	void AimBot(Entity* target);
	std::optional<Entity> GetClosest();

}

