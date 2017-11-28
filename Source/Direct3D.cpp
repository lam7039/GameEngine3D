#include <Windows.h>
#include "Direct3D.h"
#include "Texture.h"

SE_BEGIN_NAMESPACE

#define VERTEX_FORMAT (D3DFVF_XYZ | D3DFVF_TEX1)

struct Vertex {
	float x, y, z;
	float tu, tv;
};

Direct3D::Direct3D(HWND hWnd) {
	m_d3d = Direct3DCreate9(D3D_SDK_VERSION);
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = true;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.hDeviceWindow = hWnd;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

	m_d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &m_d3dDev);

	/*Vertex vertices[] = {
		{ -1.0f, 1.0f, 0.0f,	0.0f, 0.0f },		//Top-left
		{ 1.0f, 1.0f, 0.0f,		1.0f, 0.0f },		//Top-right
		{ -1.0f,-1.0f, 0.0f,	0.0f, 1.0f },		//Bottom-left
		{ 1.0f,-1.0f, 0.0f,		1.0f, 1.0f },		//Bottom-right
	};

	int vertCount = sizeof(vertices) / sizeof(Vertex);
	int byteCount = vertCount * sizeof(Vertex);
	if (FAILED(m_d3dDev->CreateVertexBuffer(byteCount, 0, VERTEX_FORMAT, D3DPOOL_MANAGED, &m_vBuffer, NULL))) {
		return;
	}

	VOID* pVertices;
	m_vBuffer->Lock(0, 0, (void**)&pVertices, 0);
	memcpy(pVertices, vertices, byteCount);
	m_vBuffer->Unlock();


	std::string src = "Assets\\texture.jpg";
	Texture texture(m_d3dDev, src);*/

	m_d3dDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE); //D3DCULL_CCW
	m_d3dDev->SetRenderState(D3DRS_LIGHTING, FALSE);
	m_d3dDev->SetRenderState(D3DRS_ZENABLE, TRUE);
	m_d3dDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	
	std::string src = "Assets\\tiger.x";
	m_mesh.Load(m_d3dDev, src);
}

void Direct3D::Update(float delta) {
	//World
	unsigned int iTime = (int)delta / 10 % 1000;
	D3DXMATRIX matRotate;
	D3DXMATRIX matTranslate;
	D3DXMatrixRotationY(&matRotate, iTime * (2.0f * D3DX_PI) / 1000.0f);
	D3DXMatrixTranslation(&matTranslate, 0.0f, 0.0f, 5.0f);
	m_d3dDev->SetTransform(D3DTS_WORLD, &(matRotate * matTranslate));
	
	//View
	D3DXMATRIX matView;
	D3DXMatrixLookAtLH(&matView,
		&D3DXVECTOR3(0.0f, 0.0f, 10.0f),
		&D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		&D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	m_d3dDev->SetTransform(D3DTS_VIEW, &matView);

	//Projection
	D3DXMATRIX matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4, 1.0f, 1.0f, 100.0f);
	m_d3dDev->SetTransform(D3DTS_PROJECTION, &matProj);
}

void Direct3D::Render() {
	m_d3dDev->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 40, 100), 1.0f, 0);
	m_d3dDev->BeginScene();

	/*m_d3dDev->SetFVF(VERTEX_FORMAT);
	m_d3dDev->SetStreamSource(0, m_vBuffer, 0, sizeof(Vertex));
	m_d3dDev->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);*/
	m_mesh.Render();

	m_d3dDev->EndScene();
	m_d3dDev->Present(NULL, NULL, NULL, NULL);
}

Direct3D::~Direct3D() {
	m_mesh.Clean();
	//m_vBuffer->Release();
	m_d3dDev->Release();
	m_d3d->Release();
}

SE_END_NAMESPACE