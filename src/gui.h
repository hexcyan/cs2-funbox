#pragma once

#include <d3d11.h>
#include <dxgi.h>

namespace gui {
	bool open = true;

	bool setup = false;

	// Windows Windows
	HWND window = nullptr;
	WNDCLASSEX windowClass = { };
	WNDPROC originalWindowProcess = nullptr;
	
	bool WindowClassSetup(const char* windowClassName) noexcept;
	void WindowClassDestroy() noexcept;

	bool WindowSetup(const char* windowName) noexcept;
	void WindowDestroy() noexcept;

	// Set up DirectX 11 device
	ID3D11Device* device = nullptr;
	ID3D11DeviceContext* deviceContext = nullptr;
	IDXGISwapChain* swapChain = nullptr;

	bool DirectXSetup() noexcept;
	void DirectXDestroy() noexcept;

	void Setup(); // Initialise DirectX Device

	// Initalise and Destroy IMGUI menu
	void MenuSetup(ID3D11Device* device, ID3D11DeviceContext* deviceContext) noexcept;
	void MenuDestroy() noexcept;

	void RenderMenu() noexcept;
}