#include <Windows.h>
#include "Direct3D.h"

SE_BEGIN_NAMESPACE

Direct3D::Direct3D() {
	m_d3d = Direct3DCreate9(D3D_SDK_VERSION);
}

void Direct3D::Init(HWND hWnd) {
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = true;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = hWnd;

	m_d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &m_d3dDev);
}

void Direct3D::Render() {
	m_d3dDev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 40, 100), 1.0f, 0);

	m_d3dDev->BeginScene();

	
	m_d3dDev->EndScene();

	m_d3dDev->Present(NULL, NULL, NULL, NULL);
}

void Direct3D::Clean() {
	m_d3dDev->Release();
	m_d3d->Release();
}

SE_END_NAMESPACE