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

	m_mesh = nullptr;
	m_meshMaterials = nullptr;
	m_meshTextures = nullptr;
	m_materialCount = 0;

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

	m_d3dDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	m_d3dDev->SetRenderState(D3DRS_LIGHTING, FALSE);
	m_d3dDev->SetRenderState(D3DRS_ZENABLE, TRUE);
	
	std::string src = "Assets\\tiger.x";
	InitGeometry(src);
}

void Direct3D::InitGeometry(const std::string &path) {
	LPD3DXBUFFER materialBuffer;
	if (FAILED(D3DXLoadMeshFromX(path.c_str(), D3DXMESH_SYSTEMMEM, m_d3dDev, NULL, &materialBuffer, NULL, &m_materialCount, &m_mesh))) {
		return;
	}
	D3DXMATERIAL* materials = (D3DXMATERIAL*)materialBuffer->GetBufferPointer();
	m_meshMaterials = new D3DMATERIAL9[m_materialCount];
	if (m_meshMaterials == NULL) {
		return;
	}
	m_meshTextures = new LPDIRECT3DTEXTURE9[m_materialCount];
	if (m_meshTextures == NULL) {
		return;
	}
	for (unsigned long i = 0; i < m_materialCount; i++) {
		m_meshMaterials[i] = materials[i].MatD3D;
		m_meshMaterials[i].Ambient = m_meshMaterials[i].Diffuse;
		m_meshTextures[i] = NULL;
		if (materials[i].pTextureFilename != NULL && lstrlen(materials[i].pTextureFilename) > 0) {
			if (FAILED(D3DXCreateTextureFromFile(m_d3dDev, materials[i].pTextureFilename, &m_meshTextures[i]))) {
				MessageBox(NULL, "Could not find texture map", "Meshes.exe", MB_OK);
				return;
			}
		}
	}
	materialBuffer->Release();
}

void Direct3D::Update(float delta) {
	//World
	unsigned int iTime = (int)delta % 1000;
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

	for (unsigned long i = 0; i < m_materialCount; i++) {
		m_d3dDev->SetMaterial(&m_meshMaterials[i]);
		m_d3dDev->SetTexture(0, m_meshTextures[i]);
		m_mesh->DrawSubset(i);
	}

	m_d3dDev->EndScene();
	m_d3dDev->Present(NULL, NULL, NULL, NULL);
}

Direct3D::~Direct3D() {
	if (m_meshMaterials != NULL) {
		delete[] m_meshMaterials;
	}
	if (m_meshTextures) {
		for (unsigned long i = 0; i < m_materialCount; i++) {
			if (m_meshTextures[i]) {
				m_meshTextures[i]->Release();
			}
		}
		delete[] m_meshTextures;
	}
	if (m_mesh != NULL) {
		m_mesh->Release();
	}

	//m_vBuffer->Release();
	m_d3dDev->Release();
	m_d3d->Release();
}

SE_END_NAMESPACE