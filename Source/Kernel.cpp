#include <Windows.h>
#include "Debug.h"
#include "Kernel.h"
#include "Window.h"
#include "FPSCounter.h"
#include "SceneLoader.h"
#include "DirectX9\Direct3D.h"

namespace se {

	Kernel::Kernel(const std::string &title, int width, int height) {
		Debug logger("engine.log");
		logger.Log(0, __FILE__, __LINE__, "Engine started");

		Window window(title, width, height);
		m_hWnd = window.OpenWindow();
		m_input.Initialize(window.GetInstance(), m_hWnd, width, height);

		m_camera.Initialize(&m_input);

		m_renderer = new Direct3D();
		m_renderer->Create(m_hWnd);
	}

	int Kernel::EnterLoop() {
		bool isRunning = true;

		MSG msg;
		FPSCounter fps;

		while (isRunning) {
			while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			m_input.Update();

			if (msg.message == WM_QUIT || m_input.IsPressed(DIK_ESCAPE)) {
				isRunning = false;
			}
			// Logic.
			m_camera.Update(fps.GetDelta());

			//World (object update)
			SceneLoader::GetInstance()->GetCurrentScene()->Update(fps.GetDelta());

			//View (camera)
			
			D3DXMATRIX matView;

			D3DXVECTOR3 position;
			D3DXVECTOR3 lookAt;
			D3DXVECTOR3 up;

			position.x = m_camera.GetPosition().X;
			position.y = m_camera.GetPosition().Y;
			position.z = m_camera.GetPosition().Z;

			lookAt.x = 0.0f;
			lookAt.y = 0.0f;
			lookAt.z = 15.0f;

			lookAt = position + lookAt;

			up.x = 0.0f;
			up.y = 1.0f;
			up.z = 0.0f;

			D3DXMatrixLookAtLH(&matView,
				&position, //position
				&lookAt, //where you're looking to
				&up);
			Direct3D::GetDevice()->SetTransform(D3DTS_VIEW, &matView);

			//Projection
			D3DXMATRIX matProj;
			D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4, 800 / 500, 1.0f, 100.0f);
			Direct3D::GetDevice()->SetTransform(D3DTS_PROJECTION, &matProj);

			m_renderer->Update(fps.GetDelta());

			// Drawing.
			m_renderer->Render();

			fps.Update();
		}

		m_renderer->Release();

		return msg.wParam;
	}

}