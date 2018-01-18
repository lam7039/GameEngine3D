#include "DirectX9/Direct3D.h"
#include "AssetManager.h"
#include "SceneManager.h"
#include "Transform.h"

namespace se {

	LPDIRECT3DDEVICE9 Direct3D::m_device = nullptr;

	void Direct3D::Create(HWND hWnd) {
		m_logger.SelectLogger("engine.log");
		m_d3d = Direct3DCreate9(D3D_SDK_VERSION);
		D3DPRESENT_PARAMETERS d3dpp;
		ZeroMemory(&d3dpp, sizeof(d3dpp));
		d3dpp.Windowed = true;
		d3dpp.SwapEffect = D3DSWAPEFFECT_COPY;
		d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
		d3dpp.hDeviceWindow = hWnd;
		d3dpp.EnableAutoDepthStencil = TRUE;
		d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

		if (FAILED(m_d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &m_device))) {
			m_logger.Log(2, __FILE__, __LINE__, "Failed to create the device");
		}

		m_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW); //D3DCULL_CCW //TODO: remove this comment when done
		m_device->SetRenderState(D3DRS_LIGHTING, FALSE);
		m_device->SetRenderState(D3DRS_ZENABLE, TRUE);
		m_device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
		m_device->SetRenderState(D3DRS_CLIPPING, TRUE);

		m_device->CreateAdditionalSwapChain(&d3dpp, &m_swapChain);
	}

	void Direct3D::Update(float delta) {

	}

	void Direct3D::Render() {
		m_device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 40, 100), 1.0f, 0);
		m_device->BeginScene();

		if (SceneManager::GetInstance()->GetSceneCount() > 0) {
			std::vector<Entity*> m_currentSceneObjects = SceneManager::GetInstance()->GetCurrentScene()->GetEntities();
			for (int i = 0; i < m_currentSceneObjects.size(); i++) {
				Transform3f *target = m_currentSceneObjects[i]->GetTarget();
				D3DXMatrixScaling(&m_scale, target->scaleX, target->scaleY, target->scaleZ);
				D3DXMatrixRotationYawPitchRoll(&m_matRotate, target->rotX, target->rotY, target->rotZ);
				D3DXMatrixTranslation(&m_matTranslate, target->posX, target->posY, target->posZ);
				m_device->SetTransform(D3DTS_WORLD, &(m_scale * m_matRotate * m_matTranslate));
				if (m_currentSceneObjects[i]->GetAssetName() != "") {
					AbstractAsset *m_currentMesh = AssetManager::GetInstance()->GetAssetList()[m_currentSceneObjects[i]->GetAssetName()];
					m_currentMesh->Process();
				}
			}
			SceneManager::GetInstance()->GetCurrentScene()->Render();
		}

		m_device->EndScene();
		m_device->Present(NULL, NULL, NULL, NULL);
	}

	void Direct3D::Release() {
		m_device->Release();
		m_d3d->Release();
	}

	LPDIRECT3DDEVICE9 Direct3D::GetDevice() {
		return m_device;
	}

}