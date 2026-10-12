#pragma once
#include <Windows.h>
#include "../../../ext/minhook/MinHook.h"
#include "../hooks/wgl/wgl.h"
#include "../../sdk/mem/mem.h"

namespace hooks
{
	bool Init();
	void Release();
	bool Init_Hooks();
}
