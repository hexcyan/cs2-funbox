#include "gui.h"

#include "../ext/imgui/imgui.h"
#include "../ext/imgui/backends/imgui_impl_dx11.h"
#include "../ext/imgui/backends/imgui_impl_win32.h"

#include <stdexcept>

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(
	HWND hWnd,
	UINT msg,
	WPARAM wParam,
	LPARAM lParam
);

LRESULT CALLBACK WindowProcess(
	HWND hWnd,
	UINT msg,
	WPARAM wParam,
	LPARAM lParam
);


bool gui::WindowClassSetup(const char* windowClassName) noexcept {
	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.style = CS_HREDRAW | CS_VREDRAW;
	windowClass.lpfnWndProc = DefWindowProc;
	windowClass.cbClsExtra = 0;
	windowClass.cbWndExtra = 0;
	windowClass.hInstance = GetModuleHandle(NULL);
	windowClass.hIcon = NULL;
	windowClass.hCursor = NULL;
	windowClass.hbrBackground = NULL;
	windowClass.lpszMenuName = windowClassName;
	windowClass.hIconSm = NULL;

	if (!RegisterClassEx(&windowClass)) {
		return false;
	} else {
		return true;
	}
}

void gui::WindowClassDestroy() noexcept {
	UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
}

bool gui::WindowSetup(const char* windowName) noexcept {
	// window to retrieve DX11 device
	window = CreateWindow(
		windowClass.lpszClassName,
		windowName,
		WS_OVERLAPPED,
		0,
		0,
		100,
		100,
		0,
		0,
		windowClass.hInstance,
		0
	);

	// Check if window was created properly
	if (!window) {
		return false;
	}
	else {
		return true;
	}
}

void gui::WindowDestroy() noexcept {
	if (window) {
		DestroyWindow(window);
	}
}

bool gui::DirectXSetup() noexcept {

}

void gui::DirectXDestroy() noexcept{}

void gui::Setup(){} // Initialise DirectX Device

// Initalise and Destroy IMGUI menu
void gui::MenuSetup(ID3D11Device* device, ID3D11DeviceContext* deviceContext) noexcept {

}
void gui::MenuDestroy() noexcept {}

void gui::RenderMenu() noexcept {}

LRESULT CALLBACK WindowProcess(
	HWND hWnd,
	UINT msg,
	WPARAM wParam,
	LPARAM lParam
) {
	// Menu Toggle
	if (GetAsyncKeyState(VK_PRIOR) & 1) {
		gui::open = !gui::open;
	}

	// Pass messages to imgui only if menu is open
	if (gui::open && ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam)) {
		return 1L;
	}

	// make game call our window process
	return CallWindowProc(
		gui::originalWindowProcess,
		hWnd,
		msg,
		wParam,
		lParam
	)
}