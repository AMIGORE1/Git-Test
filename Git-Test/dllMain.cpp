#include <Windows.h>
#include <iostream>
#include <thread>

static HANDLE mainThread = nullptr;

DWORD WINAPI Agyzak(LPVOID hModule)
{

#ifdef _DEBUG
	AllocConsole();
	FILE* f;
	freopen_s(&f, "CONOUT$", "w", stdout);
#endif



	while (!(GetAsyncKeyState(VK_END) & 1))
		std::this_thread::sleep_for(std::chrono::milliseconds(150));


#ifdef _DEBUG
	if (f) fclose(f);
	FreeConsole();
#endif
	FreeLibraryAndExitThread(static_cast<HMODULE>(hModule), 0);
	return 0;
}

BOOL WINAPI DllMain(HMODULE hModule, DWORD reason, LPVOID lp)
{
	if (reason == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(hModule);
		mainThread = CreateThread(nullptr,
			0,
			Agyzak,
			hModule,
			0,
			nullptr);
	}
	return TRUE;
}