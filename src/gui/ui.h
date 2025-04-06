#ifndef UI_H
#define UI_H

#include <Windows.h>
#include <d3d11.h>
#include <tchar.h>
#include <wincodec.h> // Windows Imaging Component headers
#pragma comment(lib, "Windowscodecs.lib") // Link against WIC
#include <vector>
#include "imgui.h"


extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

class UI
{
private:
	static ID3D11Device* pd3dDevice;
	static ID3D11DeviceContext* pd3dDeviceContext;
	static IDXGISwapChain* pSwapChain;
	static ID3D11RenderTargetView* pMainRenderTargetView;
	

	static bool CreateDeviceD3D(HWND hWnd);
	static void CleanupDeviceD3D();
	static void CreateRenderTarget();
	static void CleanupRenderTarget();
	static LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	static void LoadResource();
	static ID3D11ShaderResourceView* LoadTextureFromFile(const wchar_t* filename);
	

public:
	static void Render(HMODULE hModule);
	static ID3D11ShaderResourceView* teamBuilderTexture;
};

#endif
