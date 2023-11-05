#include "offsets.h"
#include "bunnies.h"

#include <thread>

// CONSTANTS
constexpr auto FL_ONGROUND = (1 << 0);
constexpr auto JUMP_FLAG = 65537;
constexpr auto GROUND_FLAG = 256;

// ON_GROUND 00000100
// JUMP      0001XXX1

// bunnies
void BHop(const HMODULE instance) noexcept {
	const auto client = reinterpret_cast<std::uintptr_t>(GetModuleHandle("client.dll"));

	while (!GetAsyncKeyState(VK_DELETE)) {
		std::this_thread::sleep_for(std::chrono::milliseconds(1));

		if (!GetAsyncKeyState(VK_SPACE)) continue;

		// set memory address for localPlayer
		const auto localPlayer = *reinterpret_cast<std::uintptr_t*>(client + Offsets::dwLocalPlayerPawn);

		if (!localPlayer) continue;

		// check localPlayer is alive lol
		const auto health = *reinterpret_cast<std::int32_t*>(localPlayer + C_BaseEntity::m_iHealth);
		if (!health) continue;

		// check localPlayer flags
		const auto flags = *reinterpret_cast<std::int32_t*>(localPlayer + C_BaseEntity::m_fFlags);

		// check on ground
		(flags & FL_ONGROUND) ?
			*reinterpret_cast<std::uintptr_t*>(client + Offsets::dwForceJump) = JUMP_FLAG :  // jump
			*reinterpret_cast<std::uintptr_t*>(client + Offsets::dwForceJump) = GROUND_FLAG;   // reset
	}

	FreeLibraryAndExitThread(instance, 0);
}