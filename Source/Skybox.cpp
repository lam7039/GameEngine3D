#include "Skybox.h"

namespace se {

	Skybox::Skybox(AbstractRenderer *renderer, const std::string &assetName, const std::string &src) : AbstractAsset(renderer, assetName) {
		m_logger.SelectLogger("engine.log");

		int faceCount = 6;
		const int squareVertCount = 6;
		m_size.Set(faceCount, squareVertCount, 0);

		float posX = (1.0f / 4.0f);
		float posY = (1.0f / 3.0f);

		Vector3f position;
		position.x = -0.5f;
		position.y = 0.5f;
		position.z = 0.5f;
		Vector3f scale;
		scale.x = 1.0f;
		scale.y = 1.0f;
		scale.z = 1.0f;

		Vertex vertices[] = {
			// Front Face.
			{ position.x, position.y, position.z,										posX * 1, posY * 1 },	// Topleft.
			{ position.x + scale.x, position.y, position.z,								posX * 2, posY * 1 },	// Topright.
			{ position.x, position.y - scale.y, position.z,								posX * 1, posY * 2 },	// Bottomleft.
			{ position.x, position.y - scale.y, position.z,								posX * 1, posY * 2 },	// Bottomleft.
			{ position.x + scale.x, position.y, position.z,								posX * 2, posY * 1 },	// Topright.
			{ position.x + scale.x, position.y - scale.y, position.z,					posX * 2, posY * 2 },	// Bottomright.
																												   
			// Bottom Face.																						   
			{ position.x, position.y - scale.y, position.z,								posX * 1, posY * 2 },	// Topleft.
			{ position.x + scale.x, position.y - scale.y, position.z,					posX * 2, posY * 2 },	// Topright.
			{ position.x, position.y - scale.y, position.z - scale.z,					posX * 1, 1.0f },		// Bottomleft.
			{ position.x, position.y - scale.y, position.z - scale.z,					posX * 1, 1.0f },		// Bottomleft.
			{ position.x + scale.x, position.y - scale.y, position.z,					posX * 2, posY * 2 },	// Topright.
			{ position.x + scale.x, position.y - scale.y, position.z - scale.z,			posX * 2, 1.0f },		// Bottomright.
																												   
			// Back Face.																						   
			{ position.x + scale.x, position.y, position.z - scale.z,					posX * 3, posY * 1 },	// Topleft.
			{ position.x, position.y, position.z - scale.z,								1.0f, posY * 1 },		// Topright.
			{ position.x + scale.x, position.y - scale.y, position.z - scale.z,			posX * 3, posY * 2 },	// Bottomleft.
			{ position.x + scale.x, position.y - scale.y, position.z - scale.z,			posX * 3, posY * 2 },	// Bottomleft.
			{ position.x, position.y, position.z - scale.z,								1.0f, posY * 1 },		// Topright.
			{ position.x, position.y - scale.y, position.z - scale.z,					1.0f, posY * 2 },		// Bottomright.
																												   
			// Top Face.																						   
			{ position.x, position.y, position.z - scale.z,								posX * 1, 0.0f },		// Topleft.
			{ position.x + scale.x, position.y, position.z - scale.z,					posX * 2, 0.0f },		// Topright.
			{ position.x, position.y, position.z,										posX * 1, posY * 1 },	// Bottomleft.
			{ position.x, position.y, position.z,										posX * 1, posY * 1 },	// Bottomleft.
			{ position.x + scale.x, position.y, position.z - scale.z,					posX * 2, 0.0f },		// Topright.
			{ position.x + scale.x, position.y, position.z,								posX * 2, posY * 1 },	// Bottomright.
																												   
			// Left Face.																						   
			{ position.x, position.y, position.z - scale.z,								0.0f, posY * 1 },		// Topleft.
			{ position.x, position.y, position.z,										posX * 1, posY * 1 },	// Topright.
			{ position.x, position.y - scale.y, position.z - scale.z,					0.0f, posY * 2 },		// Bottomleft.
			{ position.x, position.y - scale.y, position.z - scale.z,					0.0f, posY * 2 },		// Bottomleft.
			{ position.x, position.y, position.z,										posX * 1, posY * 1 },	// Topright.
			{ position.x, position.y - scale.y, position.z,								posX * 1, posY * 2 },	// Bottomright.
																												   
			// Right Face.																						   
			{ position.x + scale.x, position.y, position.z,								posX * 2, posY * 1 },	// Topleft.
			{ position.x + scale.x, position.y, position.z - scale.z,					posX * 3, posY * 1 },	// Topright.
			{ position.x + scale.x, position.y - scale.y, position.z,					posX * 2, posY * 2 },	// Bottomleft.
			{ position.x + scale.x, position.y - scale.y, position.z,					posX * 2, posY * 2 },	// Bottomleft.
			{ position.x + scale.x, position.y, position.z - scale.z,					posX * 3, posY * 1 },	// Topright.
			{ position.x + scale.x, position.y - scale.y, position.z - scale.z,			posX * 3, posY * 2 },	// Bottomright.
		};

		m_renderer->CreateVertexBuffer(m_assetName, RENDERTYPE_SKYBOX, vertices, &m_size);
		m_renderer->InitializeTextureArray(m_assetName, 1);
		m_renderer->CreateTexture(m_assetName, src, 0);
	}

	void Skybox::Render() {
		m_renderer->SetSamplerState(0, SAMP_MAGFILTER, TEXF_LINEAR);
		m_renderer->SetSamplerState(0, SAMP_MINFILTER, TEXF_LINEAR);
		m_renderer->SetFVF(true, false, false, true);
		m_renderer->SetStreamSource(0, m_assetName, 0);
		m_renderer->SetTexture(0, m_assetName, 0);
		m_renderer->DrawPrimitive(m_assetName, PT_TRIANGLELIST);
	}

	void Skybox::Release() {
		m_renderer->Release(m_assetName);
	}

}