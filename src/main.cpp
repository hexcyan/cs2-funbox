#define WIN32_LEAN_AND_MEAN
#define WIN64_LEAN_AND_MEAN

#include <Windows.h>
#include <cstdint>
#include <thread>

#define FL_ONGROUND (1 << 0)
#define JUMP_WORD 65537
#define GROUND_WORD 256

namespace Offsets {
	constexpr std::ptrdiff_t dwLocalPlayer = 0x1875C48;
	constexpr std::ptrdiff_t dwForceJump = 0x1690100;

	constexpr std::ptrdiff_t m_iHealth = 0x32c;
	constexpr std::ptrdiff_t m_fFlags = 0x3c8;
}

// bunnies
void BHop(const HMODULE instance) noexcept {
	const auto client = reinterpret_cast<std::uintptr_t>(GetModuleHandle("client.dll"));

	while (!GetAsyncKeyState(VK_DELETE)) {
		std::this_thread::sleep_for(std::chrono::milliseconds(1));

		if (!GetAsyncKeyState(VK_SPACE)) continue;

		// set memory address for localPlayer
		const auto localPlayer = *reinterpret_cast<std::uintptr_t*>(client + Offsets::dwLocalPlayer);

		if (!localPlayer) continue;

		// check localPlayer is alive lol
		const auto health = *reinterpret_cast<std::int32_t*>(localPlayer + Offsets::m_iHealth);
		if (!health) continue;

		// check localPlayer flags
		const auto flags = *reinterpret_cast<std::int32_t*>(localPlayer + Offsets::m_fFlags);

		// check on ground
		(flags & FL_ONGROUND) ?
			*reinterpret_cast<std::uintptr_t*>(client + Offsets::dwForceJump) = JUMP_WORD :  // jump
			*reinterpret_cast<std::uintptr_t*>(client + Offsets::dwForceJump) = GROUND_WORD;   // reset
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




