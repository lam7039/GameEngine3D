#include <Windows.h>
#include "Direct3D.h"
#include <d3dx9.h>

SE_BEGIN_NAMESPACE

#define VERTEX_FORMAT (D3DFVF_XYZ | D3DFVF_DIFFUSE)

struct Vertex {
	float x, y, z;
	DWORD color;
};

Direct3D::Direct3D(HWND hWnd) {
	m_d3d = Direct3DCreate9(D3D_SDK_VERSION);
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = true;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.hDeviceWindow = hWnd;

	m_d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &m_d3dDev);

	Vertex vertices[] = {
		{ -1.0f,-1.0f, 0.0f, D3DCOLOR_XRGB(0, 0, 255) },
		{ 1.0f,-1.0f, 0.0f, D3DCOLOR_XRGB(0, 255, 0) },
		{ 0.0f, 1.0f, 0.0f, D3DCOLOR_XRGB(255, 0, 0) }
	};

	if (FAILED(m_d3dDev->CreateVertexBuffer(3 * sizeof(Vertex), 0, VERTEX_FORMAT, D3DPOOL_MANAGED, &m_vBuffer, NULL))) {
		return;
	}

	VOID* pVertices;
	m_vBuffer->Lock(0, 0, (void**)&pVertices, 0);
	memcpy(pVertices, vertices, sizeof(vertices));
	m_vBuffer->Unlock();

	m_d3dDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	m_d3dDev->SetRenderState(D3DRS_LIGHTING, FALSE);
}

void Direct3D::Update(float delta) {
	D3DXMATRIX world;

	UINT iTime = (int)delta % 1000;
	D3DXMatrixRotationY(&world, iTime * (2.0f * D3DX_PI) / 1000.0f);
	m_d3dDev->SetTransform(D3DTS_WORLD, &world);

	D3DXMATRIX matView;
	D3DXMatrixLookAtLH(	&matView, 
						&D3DXVECTOR3(0.0f, 0.0f, 10.0f), 
						&D3DXVECTOR3(0.0f, 0.0f, 0.0f), 
						&D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	m_d3dDev->SetTransform(D3DTS_VIEW, &matView);

	D3DXMATRIX matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4, 1.0f, 1.0f, 100.0f);
	m_d3dDev->SetTransform(D3DTS_PROJECTION, &matProj);
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