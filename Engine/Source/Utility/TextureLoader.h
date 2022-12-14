#pragma once

#include <Core/Core.h>

namespace DirectX
{
	class ScratchImage;
	struct TexMetadata;
}

namespace STL
{
	class ENGINE_API TextureLoader
	{
	public:
		static ID3D11ShaderResourceView* CreateShaderResourceView(
			ID3D11Device* device,
			const std::wstring& filename
		);

		static void Release();

		static std::unordered_map<std::wstring, ID3D11ShaderResourceView*> textureMap;

	private:
		static ID3D11ShaderResourceView* LoadNormalTextureFromFile(
			ID3D11Device* device, const std::wstring& filename, DirectX::ScratchImage& image
		);
		static ID3D11ShaderResourceView* LoadCubemapTextureFromFile(
			ID3D11Device* device, const std::wstring& filename, DirectX::ScratchImage& image
		);
		static D3D11_SRV_DIMENSION GetViewDimension(DirectX::TexMetadata& texMetadata);
	};
}