#pragma once

#include <cstddef>

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