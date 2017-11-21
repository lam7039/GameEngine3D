#include <Windows.h>
#include "Direct3D.h"

SE_BEGIN_NAMESPACE

#define VERTEX_FORMAT (D3DFVF_XYZRHW | D3DFVF_DIFFUSE)

struct Vertex {
	FLOAT x, y, z, rhw;
	DWORD color;
};

Direct3D::Direct3D(HWND hWnd) {
	m_d3d = Direct3DCreate9(D3D_SDK_VERSION);
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = true;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = hWnd;

	m_d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &m_d3dDev);

	Vertex vertices[] = {
		{ 320.0f, 50.0f, 1.0f, 1.0f, D3DCOLOR_XRGB(0, 0, 255) },
		{ 520.0f, 400.0f, 1.0f, 1.0f, D3DCOLOR_XRGB(0, 255, 0) },
		{ 120.0f, 400.0f, 1.0f, 1.0f, D3DCOLOR_XRGB(255, 0, 0) }
	};

	m_d3dDev->CreateVertexBuffer(sizeof(vertices), 0, VERTEX_FORMAT, D3DPOOL_MANAGED, &m_vBuffer, NULL);
	
	VOID* pVoid;
	m_vBuffer->Lock(0, 0, (void**)&pVoid, 0);
	memcpy(pVoid, vertices, sizeof(vertices));
	m_vBuffer->Unlock();
}

void Direct3D::Render() {
	m_d3dDev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 40, 100), 1.0f, 0);

	m_d3dDev->BeginScene();

	m_d3dDev->SetFVF(VERTEX_FORMAT);
	m_d3dDev->SetStreamSource(0, m_vBuffer, 0, sizeof(Vertex));
	m_d3dDev->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1);

	m_d3dDev->EndScene();

	m_d3dDev->Present(NULL, NULL, NULL, NULL);
}

Direct3D::~Direct3D() {
	m_vBuffer->Release();
	m_d3dDev->Release();
	m_d3d->Release();
}

SE_END_NAMESPACE