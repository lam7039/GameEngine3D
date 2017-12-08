#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include "std.h"
#include "Mesh.h"
#include <map>

//TODO: use d3d in direct3d class, not in the manager so the user use the assetloader
namespace se {

	class AssetLoader {
	public:
		void Init(LPDIRECT3DDEVICE9 device);
		void AddMesh(const std::string &path);
		void ReleaseMesh(const std::string &filename);
		static AssetLoader *GetInstance();
		std::map<std::string, Mesh> *GetMeshes();
	private:
		static AssetLoader *m_instance;
		LPDIRECT3DDEVICE9 m_device;
		std::map<std::string, Mesh> m_meshes;
		AssetLoader();
		~AssetLoader();
	};

	/* void LoadAsset(const std::string &path);
	 void ReleaseAsset(const std::string &path);*/

}

#endif