#ifndef DIRECT3D_H
#define DIRECT3D_H

#include "Renderer.h"
#include "Debug.h"
#include <d3d9.h>
#include <d3dx9.h>
#include <unordered_map>

namespace se {

	///
	/// A structure for getting relevant components.
	///
	struct DrawComponents {
		D3DMATERIAL9 *materials;
		LPD3DXMESH mesh = nullptr;
		LPDIRECT3DVERTEXBUFFER9 buffer;
		LPDIRECT3DTEXTURE9 *textures;
		int primitiveCount = 0;
		int textureCount = 0;
		bool mipMap = false;
	};

	///
	/// The renderer for DirectX 9.
	///
	class Direct3D : public AbstractRenderer {
	public:
		///
		/// Creates a DirectX renderer for the latest created Window in WindowManager, it creates a new SwapChain and adds it to the list.
		///
		void Create(int width, int height) override;
		///
		/// Updates the view for the latest added camera.
		///
		void Update(float delta) override;
		///
		/// Release all the swapchains, the device and direct3d.
		///
		void Release() override;
		///
		/// Release all components of a single DrawComponents with the buffername in the componentslist.
		///
		void Release(const std::string &bufferName) override;
		///
		/// Initialize a texture array to create texture(s) within that list to a given buffer.
		///
		void InitializeTextureArray(const std::string &bufferName, int size) override;
		///
		/// Create a vertex buffer for a specific RenderType with the referenced vertices array and size for the primitivecount.
		///
		void CreateVertexBuffer(const std::string &bufferName, RenderType type, Vertex *vertices, Vector3i *size = nullptr) override;
		///
		/// To create a texture the texture array needs to be initialized with InitializeTextureArray to a given buffer.
		///
		void CreateTexture(const std::string &bufferName, const std::string &path, int id) override;
		///
		/// Create a mesh with an .x file with the DirectX9 default pipeline to a given buffer.
		///
		void CreateMesh(const std::string &bufferName, const std::string &path) override;
		///
		/// Set the vertex type.
		///
		void SetFVF(bool coords, bool diffuse, bool specular, bool texture) override;
		///
		/// Set the sampler stage state value.
		///
		void SetSamplerState(int sampler, SamplerStateType samplerStateType, TextureFilterType textureFilterType) override;
		///
		/// Set the texture to the given buffer.
		///
		void SetTexture(int stage, const std::string &bufferName, int index) override;
		///
		/// Set the material to the given buffer.
		///
		void SetMaterial(const std::string &bufferName, int index) override;
		///
		/// Bind a vertex buffer to a device data stream.
		///
		void SetStreamSource(unsigned int streamNumber, const std::string &bufferName, unsigned int offsetInBytes, unsigned int stride = NULL) override;
		///
		/// Draw the buffer, if you draw a vertexbuffer you can set a PrimitiveType.
		///
		void Draw(const std::string &bufferName, PrimitiveType primitiveType = PT_TRIANGLELIST) override;
		///
		/// Clear the target and/or z-buffer.
		///
		void Clear(bool target, bool zBuffer) override;
		///
		/// Set the target swapchain which to render to, sets index automatically in Present() by default.
		///
		void SetRenderTarget(int index = -1) override;
		///
		/// Set the world transformations.
		///
		void SetTransform(Vector3f position, Vector3f scale, Vector3f rotation) override;
		///
		/// Begin the scene on which to draw.
		///
		void BeginScene() override;
		///
		/// End the scene on which to draw.
		///
		void EndScene() override;
		///
		/// Present the current swapchain, by default it sets it and changes the current swapchain.
		///
		void Present(int index = -1) override;
		///
		/// Set the position and rotation for the screen view.
		///
		void SetViewTransform(Vector3f position, Vector3f rotation) override;
		///
		/// Get the current axes of the view.
		///
		Vector3f GetViewAxes() override;
	private:
		// Debug.
		Debug m_logger;

		// Window.
		Vector3i m_size;
		int m_currentRenderTarget;

		// View.
		float m_viewPitch;
		float m_viewYaw;
		Vector3f m_viewPosition;
		Vector3f m_viewRotation;

		// Devices.
		LPDIRECT3D9 m_d3d;
		LPDIRECT3DDEVICE9 m_device;
		std::vector<LPDIRECT3DSWAPCHAIN9> m_swapChains;

		// Components.
		std::unordered_map<std::string, DrawComponents> m_drawComponents;

		// World.
		D3DXMATRIX m_scale;
		D3DXMATRIX m_matRotate;
		D3DXMATRIX m_matTranslate;
	};

}

#endif