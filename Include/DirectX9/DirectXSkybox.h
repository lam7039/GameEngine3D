#ifndef DIRECTXSKYBOX_H
#define DIRECTXSKYBOX_H

#include "std.h"
#include "DirectX9\Direct3D.h"
#include "Skybox.h"
#include "Asset.h"
#include "Debug.h"

namespace se {

	class Skybox : public AbstractSkybox {
	public:
		Skybox();
		void Create(Transform3f transform, const std::string &src) override;
		void Process() override;
		void Release() override;
	private:
		Debug m_logger;

		LPDIRECT3DVERTEXBUFFER9 m_vertexBuffer;
		LPDIRECT3DTEXTURE9 m_texture;

		D3DXMATRIX m_matRotate;
		D3DXMATRIX m_matTranslate;
		int m_faceCount;
	};

}

#endif