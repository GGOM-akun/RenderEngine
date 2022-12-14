#include "Core.h"
#include "TextureLoader.h"
#include <DirectXTex.h>
#include <Utility/STLException.h>

namespace STL
{
	std::unordered_map<std::wstring, ID3D11ShaderResourceView*> TextureLoader::textureMap;

	ID3D11ShaderResourceView* TextureLoader::LoadNormalTextureFromFile(
		ID3D11Device* device, const std::wstring& filename, DirectX::ScratchImage& image)
	{
		ID3D11Texture2D* texture = nullptr;
		auto result = DirectX::CreateTexture(
			device,
			image.GetImages(),
			image.GetImageCount(),
			image.GetMetadata(),
			reinterpret_cast<ID3D11Resource**>(&texture)
		);

		ThrowIfFailed(result, "Failed to create texture with 2d texture.");

		D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
		srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		srvDesc.Texture2D.MipLevels = 1;
		srvDesc.Format = image.GetMetadata().format;

		ID3D11ShaderResourceView* shaderResourceView = nullptr;
		result = device->CreateShaderResourceView(texture, &srvDesc, &shaderResourceView);
		ThrowIfFailed(result, "TextureLoader::LoadNormalTextureFromFile(), Failed to create shader resource view");

		textureMap.insert({ filename, shaderResourceView });

		SafeRelease(texture);
		return shaderResourceView;
	}

	D3D11_SRV_DIMENSION TextureLoader::GetViewDimension(DirectX::TexMetadata& texMetadata)
	{
		if (texMetadata.miscFlags == DirectX::TEX_MISC_TEXTURECUBE)
		{
			return D3D11_SRV_DIMENSION_TEXTURECUBE;
		}

		switch (texMetadata.dimension)
		{
		case DirectX::TEX_DIMENSION_TEXTURE1D:
			return D3D11_SRV_DIMENSION_TEXTURE1D;

		case DirectX::TEX_DIMENSION_TEXTURE2D:
			return D3D11_SRV_DIMENSION_TEXTURE2D;

		case DirectX::TEX_DIMENSION_TEXTURE3D:
			return D3D11_SRV_DIMENSION_TEXTURE3D;
		}

		return D3D11_SRV_DIMENSION_TEXTURE2D;
	}

	ID3D11ShaderResourceView* TextureLoader::LoadCubemapTextureFromFile(
		ID3D11Device* device, const std::wstring& filename, DirectX::ScratchImage& image)
	{
		ID3D11Texture3D* texture = nullptr;
		DirectX::TexMetadata metaData = image.GetMetadata();
		auto result = DirectX::CreateTexture(
			device, 
			image.GetImages(), 
			image.GetImageCount(), 
			metaData,
			reinterpret_cast<ID3D11Resource**>(&texture)
		);

		ThrowIfFailed(result, "TextureLoader::LoadCubemapTextureFromFile(), Failed to create texture with cubemap");

		// ?????? ?????? ?? ????.
		D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc = {};
		shaderResourceViewDesc.ViewDimension = GetViewDimension(metaData);
		shaderResourceViewDesc.Texture3D.MostDetailedMip = 0;
		shaderResourceViewDesc.Texture3D.MipLevels = 1;
		shaderResourceViewDesc.Format = image.GetMetadata().format;

		ID3D11ShaderResourceView* shaderResourceView = nullptr;
		result = device->CreateShaderResourceView(texture, &shaderResourceViewDesc, &shaderResourceView);
		ThrowIfFailed(result, "Failed to create shader resource view");

		textureMap.insert({ filename, shaderResourceView });

		SafeRelease(texture);
		return shaderResourceView;
	}

	ID3D11ShaderResourceView* TextureLoader::CreateShaderResourceView(ID3D11Device* device, const std::wstring& filename)
	{
		auto search = textureMap.find(filename);
		if (search != textureMap.end())
		{
			return search->second;
		}

		std::wstring extension = filename.substr(filename.find_last_of(TEXT(".")) + 1);
		std::transform(extension.begin(), extension.end(), extension.begin(), tolower);

		static auto basePath = std::filesystem::current_path().parent_path();

		auto finalPath = basePath;
		finalPath /= "Content\\Textures";
		finalPath /= filename;

		DirectX::ScratchImage image;
		HRESULT result = E_FAIL;
		if (extension == TEXT("tga") || extension == TEXT("targa"))
		{
			result = DirectX::LoadFromTGAFile(finalPath.c_str(), nullptr, image);
			ThrowIfFailed(result, "Failed to load scratch image with targa file.");
			return LoadNormalTextureFromFile(device, filename, image);
		}
		else if (extension == TEXT("dds"))
		{
			result = DirectX::LoadFromDDSFile(finalPath.c_str(), DirectX::DDS_FLAGS_NONE, nullptr, image);
			ThrowIfFailed(result, "Failed to load scratch image with dds file.");
			return LoadCubemapTextureFromFile(device, filename, image);
		}
		else
		{
			result = DirectX::LoadFromWICFile(finalPath.c_str(), DirectX::WIC_FLAGS_NONE, nullptr, image);
			ThrowIfFailed(result, "Failed to load scratch image.");
			return LoadNormalTextureFromFile(device, filename, image);
		}
	}

	void TextureLoader::Release()
	{
		for (auto pair : textureMap)
		{
			SafeRelease(pair.second);
		}
	}
}