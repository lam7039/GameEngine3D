#include "DirectX9/Direct3D.h"
#include "AssetManager.h"
#include "SceneManager.h"
#include "WindowManager.h"

namespace se {

	void Direct3D::Create(int width, int height) {
		m_logger.SelectLogger("engine.log");
		D3DPRESENT_PARAMETERS d3dpp;
		ZeroMemory(&d3dpp, sizeof(d3dpp));
		d3dpp.Windowed = true;
		d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
		d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
		d3dpp.hDeviceWindow = WindowManager::GetInstance()->GetWindowList()[WindowManager::GetInstance()->GetWindowCount() - 1].GetWindowHandle();
		d3dpp.EnableAutoDepthStencil = TRUE;
		d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

		if (!m_d3d || !m_device) {
			m_d3d = Direct3DCreate9(D3D_SDK_VERSION);
			if (FAILED(m_d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, d3dpp.hDeviceWindow, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &m_device))) {
				m_logger.Log(ERRORTYPE_ERROR, __FILE__, __LINE__, "Failed to create the device");
			}
		}

		LPDIRECT3DSWAPCHAIN9 swapChain;
		m_device->CreateAdditionalSwapChain(&d3dpp, &swapChain);
		m_swapChains.push_back(swapChain);

		m_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
		m_device->SetRenderState(D3DRS_LIGHTING, FALSE);
		m_device->SetRenderState(D3DRS_ZENABLE, TRUE);
		m_device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
		m_device->SetRenderState(D3DRS_CLIPPING, TRUE);

		m_size.Set(width, height, 0);
		m_viewPosition.z = -15.0f;
	}

	void Direct3D::InitializeTextureArray(const std::string &bufferName, int size) {
		DrawComponents &drawComponent = m_drawComponents[bufferName];
		drawComponent.textures = new LPDIRECT3DTEXTURE9[size];
		drawComponent.textureCount = size;
	}

	void Direct3D::CreateVertexBuffer(const std::string &bufferName, RenderType type, Vertex *vertices, Vector3i *size) {
		DrawComponents &drawComponent = m_drawComponents[bufferName];
		drawComponent = DrawComponents();
		int byteCount;
		if (type == RENDERTYPE_TERRAIN) {
			byteCount = size->x * size->y * size->z * sizeof(Vertex);
			drawComponent.mipMap = true;
			drawComponent.primitiveCount = size->x * size->y * 2;
		}
		else if (type == RENDERTYPE_SKYBOX) {
			byteCount = size->x * size->y * sizeof(Vertex);
			drawComponent.primitiveCount = size->x * 2;
		}
		else {
			m_logger.Log(ERRORTYPE_ERROR, __FILE__, __LINE__, "RenderType not supported");
			return;
		}

		if (FAILED(m_device->CreateVertexBuffer(byteCount, 0, D3DFVF_XYZ | D3DFVF_TEX1, D3DPOOL_MANAGED, &drawComponent.buffer, NULL))) {
			m_logger.Log(ERRORTYPE_ERROR, __FILE__, __LINE__, "Failed create vertex buffer");
			return;
		}

		VOID* pVertices;
		drawComponent.buffer->Lock(0, byteCount, (void**)&pVertices, 0);
		memcpy(pVertices, &*vertices, byteCount);
		drawComponent.buffer->Unlock();
	}

	void Direct3D::CreateTexture(const std::string &bufferName, const std::string &path, int id) {
		if (FAILED(D3DXCreateTextureFromFile(m_device, path.c_str(), &m_drawComponents[bufferName].textures[id]))) {
			m_logger.Log(ERRORTYPE_ERROR, __FILE__, __LINE__, "Failed to load texture for buffer: " + bufferName);
			return;
		}
	}

	void Direct3D::CreateMesh(const std::string &bufferName, const std::string &path) {
		DrawComponents &drawComponent = m_drawComponents[bufferName];
		drawComponent = DrawComponents();
		DWORD materialCount;
		LPD3DXBUFFER materialBuffer;
		if (FAILED(D3DXLoadMeshFromX(path.c_str(), D3DXMESH_SYSTEMMEM, m_device, NULL, &materialBuffer, NULL, &materialCount, &drawComponent.mesh))) {
			m_logger.Log(ERRORTYPE_ERROR, __FILE__, __LINE__, "Failed to load mesh: " + path + " count: " + std::to_string(materialCount));
			return;
		}
		D3DXMATERIAL *materials = (D3DXMATERIAL*)materialBuffer->GetBufferPointer();
		drawComponent.materials = new D3DMATERIAL9[materialCount];
		InitializeTextureArray(bufferName, materialCount);

		for (DWORD i = 0; i < materialCount; i++) {
			drawComponent.materials[i] = materials[i].MatD3D;
			drawComponent.materials[i].Ambient = drawComponent.materials[i].Diffuse;
			drawComponent.textures[i] = NULL;
			if (materials[i].pTextureFilename != NULL && lstrlen(materials[i].pTextureFilename) > 0) {
				std::string src = "Assets\\";
				src += materials[i].pTextureFilename;
				CreateTexture(bufferName, src, i);
			}
		}
		materialBuffer->Release();
	}

	void Direct3D::SetViewTransform(Vector3f position, Vector3f rotation) {
		m_viewPosition = position;
		m_viewRotation = rotation;
	}

	Vector3f Direct3D::GetViewAxes() {
		return Vector3f(m_viewYaw, m_viewPitch, 0.0f);
	}

	void Direct3D::Update(float delta) {
		m_viewPitch = D3DXToRadian(m_viewRotation.x);
		m_viewYaw = D3DXToRadian(m_viewRotation.y) - (D3DX_PI / 2);

		D3DXVECTOR3 position;
		position.x = m_viewPosition.x;
		position.y = m_viewPosition.y;
		position.z = m_viewPosition.z;

		D3DXVECTOR3 lookAt;
		lookAt.x = 0.0f;
		lookAt.y = 0.0f;
		lookAt.z = 15.0f;

		D3DXVECTOR3 up;
		up.x = 0.0f;
		up.y = 1.0f;
		up.z = 0.0f;

		D3DXMATRIX rotation;
		D3DXMatrixRotationYawPitchRoll(&rotation, m_viewYaw + (D3DX_PI / 2), m_viewPitch, 0.0f);
		D3DXVec3TransformCoord(&lookAt, &lookAt, &rotation);
		D3DXVec3TransformCoord(&up, &up, &rotation);

		lookAt = position + lookAt;

		//View.
		D3DXMATRIX m_matView;
		D3DXMatrixLookAtLH(&m_matView, &position, &lookAt, &up);
		m_device->SetTransform(D3DTS_VIEW, &m_matView);

		//Projection.
		D3DXMATRIX matProj;
		D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4, m_size.x / m_size.y, 1.0f, 1000.0f);
		m_device->SetTransform(D3DTS_PROJECTION, &matProj);
	}

	void Direct3D::Render(const std::string &bufferName) {
		DrawComponents &drawComponent = m_drawComponents[bufferName];
		m_device->SetFVF(D3DFVF_XYZ | D3DFVF_TEX1);
		m_device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
		m_device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
		if (drawComponent.mipMap) {
			m_device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
		}
		else {
			m_device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_NONE);
		}
		if (drawComponent.mesh) {
			for (int i = 0; i < drawComponent.textureCount; i++) {
				m_device->SetMaterial(&drawComponent.materials[i]);
				m_device->SetTexture(i, drawComponent.textures[i]);
				drawComponent.mesh->DrawSubset(i);
			}
		}
		else {
			m_device->SetStreamSource(0, drawComponent.buffer, 0, sizeof(Vertex));
			m_device->SetTexture(0, drawComponent.textures[0]);
			m_device->DrawPrimitive(D3DPT_TRIANGLELIST, 0, drawComponent.primitiveCount);
		}
	}

	void Direct3D::Process() {
		for (int i = 0; i < m_swapChains.size(); i++) {
			m_device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 40, 100), 1.0f, 0);

			LPDIRECT3DSURFACE9 backBuffer;
			m_swapChains[i]->GetBackBuffer(0, D3DBACKBUFFER_TYPE_MONO, &backBuffer);
			m_device->SetRenderTarget(0, backBuffer);

			m_device->BeginScene();

			// Sets the positions of the entities and renders them on the active scene.
			if (SceneManager::GetInstance()->GetSceneCount() > 0) {
				std::vector<Entity*> m_currentSceneEntities = SceneManager::GetInstance()->GetCurrentScene()->GetEntities();
				for (int j = 0; j < m_currentSceneEntities.size(); j++) {
					Vector3f *position = m_currentSceneEntities[j]->GetPosition();
					Vector3f *scale = m_currentSceneEntities[j]->GetScale();
					Vector3f *rotation = m_currentSceneEntities[j]->GetRotation();
					D3DXMatrixScaling(&m_scale, scale->x, scale->y, scale->z);
					D3DXMatrixRotationYawPitchRoll(&m_matRotate, rotation->x, rotation->y, rotation->z);
					D3DXMatrixTranslation(&m_matTranslate, position->x, position->y, position->z);
					m_device->SetTransform(D3DTS_WORLD, &(m_scale * m_matRotate * m_matTranslate));
					std::string assetName = m_currentSceneEntities[j]->GetAssetName();
					if (assetName != "") {
						AbstractAsset *currentAsset = AssetManager::GetInstance()->GetAssetList()[assetName];
						if (currentAsset) {
							currentAsset->Render();
						}
					}
				}
			}

			m_device->EndScene();
			m_swapChains[i]->Present(NULL, NULL, WindowManager::GetInstance()->GetWindowList()[i].GetWindowHandle(), NULL, 0);
		}
	}

	void Direct3D::Release() {
		for (int i = 0; i < m_device->GetNumberOfSwapChains(); i++) {
			LPDIRECT3DSWAPCHAIN9 swapChain;
			m_device->GetSwapChain(i, &swapChain);
			swapChain->Release();
		}
		m_device->Release();
		m_d3d->Release();
	}

	void Direct3D::Release(const std::string &bufferName) {
		DrawComponents &drawComponent = m_drawComponents[bufferName];
		if (drawComponent.mesh) {
			drawComponent.mesh->Release();
		}
		for (int i = 0; i < drawComponent.textureCount; i++) {
			drawComponent.textures[i]->Release();
		}
	}

}