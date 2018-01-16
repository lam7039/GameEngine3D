#ifndef DIRECTXSKYBOX_H
#define DIRECTXSKYBOX_H

#include "std.h"
#include "DirectX9\Direct3D.h"
#include "Skybox.h"
#include "Asset.h"
#include "Debug.h"
#include "Transform.h"

namespace se {

	class Skybox : public AbstractSkybox {
	public:
		void Create(const std::string &topSrc, const std::string &bottomSrc, const std::string &leftSrc, const std::string &rightSrc) override;
		void Process() override;
		void Release() override;
		void SetPosition(float x, float y, float z);
		void SetRotation(float x, float y, float z);
		void SetScale(float x, float y, float z);
	private:
		LPD3DXMESH m_mesh;
		LPDIRECT3DCUBETEXTURE9 m_map;
		Debug m_logger;
		Transform3f m_transform;
		std::string m_topSrc;
		std::string m_bottomSrc;
		std::string m_leftSrc;
		std::string m_rightSrc;
	};

}

#endif