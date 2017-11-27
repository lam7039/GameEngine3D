#ifndef TEXTURE_H
#define TEXTURE_H

#include "std.h"
#include <d3dx9.h>

SE_BEGIN_NAMESPACE

class Texture {
public:
	Texture();
	~Texture();
	void CreateTexture(LPDIRECT3DDEVICE9 device, const std::string &source);
private:
	LPDIRECT3DTEXTURE9 m_texture;
};

SE_END_NAMESPACE

#endif