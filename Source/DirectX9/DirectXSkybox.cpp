#include "DirectX9\DirectXSkybox.h"

namespace se {

	void Skybox::Create() {
		m_mesh = new Mesh();
		m_mesh->SetPath("ball.x");
		m_mesh->Create();
	}

	void Skybox::Load() {
		m_mesh->Load();
	}

	void Skybox::Process() {
		m_mesh->Process();
	}

	void Skybox::Release() {
		m_mesh->Release();
	}

}