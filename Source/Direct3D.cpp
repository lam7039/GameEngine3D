#include <Windows.h>
#include "Direct3D.h"
#include "AssetLoader.h"

SE_BEGIN_NAMESPACE

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

	m_d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &m_device);
	m_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW); //D3DCULL_CCW
	m_device->SetRenderState(D3DRS_LIGHTING, FALSE);
	m_device->SetRenderState(D3DRS_ZENABLE, TRUE);
	m_device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	
	AssetLoader *loader = AssetLoader::GetInstance();
	loader->Init(m_device);

	m_airplane.Init("airplane.x");
	m_tiger.Init("tiger.x");

	m_airplane.SetPosition(2.0f, 0.0f, -5.0f);
	m_tiger.SetPosition(-2.0f, -0.0f, 0.0f);
}

Direct3D::~Direct3D() {
	AssetLoader::GetInstance()->Clean("tiger.x");
	AssetLoader::GetInstance()->Clean("airplane.x");
	m_device->Release();
	m_d3d->Release();
}

void Direct3D::Update(float delta) {
	//World (object update)
	unsigned int iTime = (int)delta / 10 % 1000;
	m_tiger.SetRotation(iTime * (2.0f * D3DX_PI) / 1000.0f, 0.0f, 0.0f);
	m_airplane.SetRotation(-(iTime * (2.0f * D3DX_PI) / 1000.0f), 0.0f, 0.0f);

	m_airplane.Update(delta);
	m_tiger.Update(delta);

	//View (camera)
	D3DXMATRIX matView;
	D3DXMatrixLookAtLH(&matView,
		&D3DXVECTOR3(0.0f, 0.0f, 10.0f),
		&D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		&D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	m_device->SetTransform(D3DTS_VIEW, &matView);

	//Projection
	D3DXMATRIX matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4, 1.0f, 1.0f, 100.0f);
	m_device->SetTransform(D3DTS_PROJECTION, &matProj);
}

void Direct3D::Render() {
	m_device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 40, 100), 1.0f, 0);
	m_device->BeginScene();

	m_airplane.Render(m_device);
	m_tiger.Render(m_device);

	m_device->EndScene();
	m_device->Present(NULL, NULL, NULL, NULL);
}

SE_END_NAMESPACE