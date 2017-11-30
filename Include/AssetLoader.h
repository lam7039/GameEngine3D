#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include "std.h"
#include "Mesh.h"
#include <map>

//TODO: use a map and call, call it in object and destroy it there too, not in the manager?
SE_BEGIN_NAMESPACE

class AssetLoader {
public:
	void Init(LPDIRECT3DDEVICE9 device);
	void AddMesh(const std::string &filename);
	void Clean(const std::string &filename);
	static AssetLoader *GetInstance();
	std::map<std::string, Mesh> *GetMeshes();
private:
	static AssetLoader *m_instance;
	LPDIRECT3DDEVICE9 m_device;
	std::map<std::string, Mesh> m_meshes;
	AssetLoader();
};

SE_END_NAMESPACE

#endif