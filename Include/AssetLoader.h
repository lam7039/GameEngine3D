#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include "std.h"
#include "Mesh.h"
#include <map>

//TODO: use d3d in direct3d class, not in the manager so the user use the assetloader
SE_BEGIN_NAMESPACE

class AssetLoader {
public:
	void Init(LPDIRECT3DDEVICE9 device);
	SE_API void AddMesh(const std::string &path);
	SE_API void ReleaseMesh(const std::string &filename);
	SE_API static AssetLoader *GetInstance();
	std::map<std::string, Mesh> *GetMeshes();
private:
	static AssetLoader *m_instance;
	LPDIRECT3DDEVICE9 m_device;
	std::map<std::string, Mesh> m_meshes;
	AssetLoader();
	~AssetLoader();
};

/*SE_API void LoadAsset(const std::string &path);
SE_API void ReleaseAsset(const std::string &path);*/

SE_END_NAMESPACE

#endif