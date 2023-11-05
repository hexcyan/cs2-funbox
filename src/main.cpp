#define WIN32_LEAN_AND_MEAN
#define WIN64_LEAN_AND_MEAN

#include <Windows.h>
#include <cstdint>
#include <thread>

// CONSTANTS
constexpr auto FL_ONGROUND = (1 << 0);
constexpr auto JUMP_FLAG = 65537;
constexpr auto GROUND_FLAG = 256;

// ON_GROUND 00000100
// JUMP      0001XXX1

namespace Offsets {
	constexpr std::ptrdiff_t dwEntityList = 0x17995C0;
	constexpr std::ptrdiff_t dwLocalPlayerPawn = 0x1886C48;

	// movement
	constexpr std::ptrdiff_t dwForceBackward = 0x169F130;
	constexpr std::ptrdiff_t dwForceForward = 0x169F0A0;
	constexpr std::ptrdiff_t dwForceLeft = 0x169F1C0;
	constexpr std::ptrdiff_t dwForceRight = 0x169F250;
	constexpr std::ptrdiff_t dwForceJump = 0x169F370;
	constexpr std::ptrdiff_t dwForceCrouch = 0x169F400;
}

namespace C_BaseEntity {
	constexpr std::ptrdiff_t m_iHealth = 0x32C;
	constexpr std::ptrdiff_t m_fFlags = 0x3C8;
}

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

// dll entry point
int __stdcall DllMain(
	const HMODULE instance, // Instance of the DLL
	const std::uintptr_t reason, // check reason of attachment/detachment
	const void* reserved
) {
	// dll process attach
	if (reason == 1) {
		DisableThreadLibraryCalls(instance);

		//our/ thread
		const auto our_thread = CreateThread(
			nullptr,
			0,
			reinterpret_cast<LPTHREAD_START_ROUTINE>(BHop),
			instance,
			0,
			nullptr
		);

		// close thread handler
		if (our_thread) {
			CloseHandle(our_thread);
		}
	}

	return 1;
}
