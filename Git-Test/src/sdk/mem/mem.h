#include <cstdint>

namespace Mem
{
	uintptr_t GetModuleBase(const char* module);
	std::uint8_t* PatternScan(void* module, const char* signature);
}