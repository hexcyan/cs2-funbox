#define WIN32_LEAN_AND_MEAN
#define WIN64_LEAN_AND_MEAN

#include "bunnies.h"

// dll entry point
int __stdcall DllMain(
	const HMODULE instance, // Instance of the DLL
	const std::uintptr_t reason, // check reason of attachment/detachment
	const void* reserved
) {
	// dll process attach
	if (reason == DLL_PROCESS_ATTACH) {
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




