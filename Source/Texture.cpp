#include "Texture.h"

SE_BEGIN_NAMESPACE

Texture::Texture() {
	m_texture = nullptr;
}

Texture::~Texture() {

}

void Texture::CreateTexture(LPDIRECT3DDEVICE9 device, const std::string &source) {
	D3DXCreateTextureFromFile(device, source.c_str(), &m_texture);
	device->SetTexture(0, m_texture);
	device->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
	device->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	device->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
}

SE_END_NAMESPACE