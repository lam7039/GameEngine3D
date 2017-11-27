#include "Texture.h"

SE_BEGIN_NAMESPACE

Texture::Texture(LPDIRECT3DDEVICE9 device, const std::string &path) {
	if (D3DXCreateTextureFromFile(device, path.c_str(), &m_texture) != D3D_OK) {
		return;
	}
	device->SetTexture(0, m_texture);
	device->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
	device->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	device->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
}

Texture::~Texture() {
	m_texture->Release();
}

SE_END_NAMESPACE