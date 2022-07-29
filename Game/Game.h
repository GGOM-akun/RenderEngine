#pragma once

#include <Core/Core.h>
#include <Core/Application.h>
#include <Renderer/VertexBuffer.h>
#include <Renderer/InputLayout.h>
#include <EngineShader/STLDefaultShader.h>
#include <EngineShader/STLPositionColorShader.h>
#include <EngineShader/STLPositionColorUVShader.h>
#include <Renderer/IndexBuffer.h>
#include <Renderer/Texture.h>
#include <Renderer/SamplerState.h>

namespace STL
{
	class Game : public Application
	{
	public:
		Game(
			HINSTANCE hInstance,
			uint32 width,
			uint32 height,
			const std::wstring& title
		);

		virtual ~Game();
		virtual void Initialize() override;
		virtual void RenderScene() override;

	private:
		VertexBuffer vertexBuffer;
		IndexBuffer indexBuffer;
		InputLayout inputLayout;
		STLPositionColorUVShader mainShader;	// 사용하고싶은 셰이더로 변경해야한다.

		// 텍스쳐 매핑 관련
		Texture texture;
		Texture texture1;
		Texture texture2;
		SamplerState samplerState;
		
		//ID3D11ShaderResourceView* texture;
		//ID3D11ShaderResourceView* texture1;
		//ID3D11SamplerState* samplerState;
	};
}