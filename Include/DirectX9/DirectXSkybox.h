#ifndef SKYBOX_H
#define SKYBOX_H

#include "std.h"
#include "DirectX9\Direct3D.h"
#include "Asset.h"
#include "Debug.h"

namespace se {

	class Skybox : public AbstractAsset {
	public:
		void Create() override;
		void Load() override;
		void Process() override;
		void Release() override;
	private:
		LPD3DXMESH m_mesh;
		LPDIRECT3DCUBETEXTURE9 m_map;
		Debug m_logger;

	};

}

#endif