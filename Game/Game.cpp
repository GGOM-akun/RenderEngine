#include "Game.h"
#include <Renderer/VertexDeclaration.h>
#include <Utility/TextureLoader.h>
#include <Utility/STLException.h>

namespace STL
{
	Game::Game(HINSTANCE hInstance, uint32 width, uint32 height, const std::wstring& title)
		: Application(hInstance, width, height, title)
	{
	}

	Game::~Game()
	{
		// 로드한 텍스처 리소스 해제
		TextureLoader::Release();
	}
	
	void Game::Initialize()
	{
		Application::Initialize();

		// 장치 참조 저장.
		auto device = deviceManager->GetDevice();

		// 정점 버퍼 생성.
		//VertexPosition vertices[] =
		//{
		//	//VertexPosition( 0.0f, 0.5f, 0.5f),
		//	//VertexPosition( 0.5f,-0.5f, 0.5f),
		//	//VertexPosition(-0.5f,-0.5f, 0.5f),

		//	//VertexPosition(-0.5f,-0.5f, 0.5f),
		//	//VertexPosition(-0.5f, 0.5f, 0.5f),
		//	//VertexPosition( 0.5f,-0.5f, 0.5f),
		//	//VertexPosition(-0.5f, 0.5f, 0.5f),
		//	//VertexPosition( 0.5f, 0.5f, 0.5f),
		//	//VertexPosition( 0.5f,-0.5f, 0.5f),

		//	VertexPosition(-0.5f,-0.5f, 0.5f),		// 왼쪽 하단.
		//	VertexPosition(-0.5f, 0.5f, 0.5f),		// 왼쪽 상단.
		//	VertexPosition( 0.5f, 0.5f, 0.5f),		// 오른쪽 상단.
		//	VertexPosition( 0.5f,-0.5f, 0.5f),		// 오른쪽 하단.
		//};

		//VertexPositionColor vertices[] =
		//{
		//	VertexPositionColor({-0.5f,-0.5f, 0.5f}, { 1.0f, 0.0f, 0.0f }),		// 왼쪽 하단.
		//	VertexPositionColor({-0.5f, 0.5f, 0.5f}, { 0.0f, 1.0f, 0.0f }),		// 왼쪽 상단.
		//	VertexPositionColor({ 0.5f, 0.5f, 0.5f}, { 0.0f, 0.0f, 1.0f }),		// 오른쪽 상단.
		//	VertexPositionColor({ 0.5f,-0.5f, 0.5f}, { 1.0f, 0.0f, 0.0f }),		// 오른쪽 하단.
		//};

		VertexPositionColorUV vertices[] =
		{
			VertexPositionColorUV({-0.5f,-0.5f, 0.5f}, { 1.0f, 0.0f, 0.0f }, { 0.0f, 1.0f }),		// 왼쪽 하단.
			VertexPositionColorUV({-0.5f, 0.5f, 0.5f}, { 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f }),		// 왼쪽 상단.
			VertexPositionColorUV({ 0.5f, 0.5f, 0.5f}, { 0.0f, 0.0f, 1.0f }, { 1.0f, 0.0f }),		// 오른쪽 상단.
			VertexPositionColorUV({ 0.5f,-0.5f, 0.5f}, { 1.0f, 1.0f, 1.0f }, { 1.0f, 1.0f }),		// 오른쪽 하단.
		};

		vertexBuffer = VertexBuffer(vertices, _countof(vertices), sizeof(vertices[0]));
		vertexBuffer.Create(device);

		// 인덱스 버퍼 생성.
		uint32 indices[] = { 0, 1, 3, 1, 2, 3 };

		indexBuffer = IndexBuffer(indices, _countof(indices));
		indexBuffer.Create(device);

		// 쉐이더 초기화.
		mainShader.Initialize(device);

		// 입력 레이아웃 생성.
		//LPCSTR SemanticName;
		//UINT SemanticIndex;
		//DXGI_FORMAT Format;
		//UINT InputSlot;
		//UINT AlignedByteOffset;
		//D3D11_INPUT_CLASSIFICATION InputSlotClass;
		//UINT InstanceDataStepRate;
		D3D11_INPUT_ELEMENT_DESC layout[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 }
		};

		inputLayout.Create(device, layout, _countof(layout), mainShader.GetVertexShaderBuffer());

		// 텍스처 로딩
		texture = Texture(L"sample.jpg");
		texture.Create(device);

		texture1 = Texture(L"jammin.jpg");
		texture1.Create(device);

		texture2 = Texture(L"jammin2.jpg");
		texture2.Create(device);

		samplerState.Create(device);

		//// 샘플러 스테이트 생성
		//D3D11_SAMPLER_DESC samplerDesc = {};
		//samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		//samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
		//samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
		//samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;

		//auto result = device->CreateSamplerState(&samplerDesc, &samplerState);
		//ThrowIfFailed(result, "failed to create sampler state");
	}
	
	void Game::RenderScene()
	{
		auto context = deviceManager->GetContext();

		// Draw 함수를 실행하기 전에 GPU에서 사용할 리소스를 모두 바인딩(연결)한다.
		// 순서는 상관 없음.
		inputLayout.Bind(context);
		vertexBuffer.Bind(context);
		mainShader.Bind(context);

		indexBuffer.Bind(context);

		texture.Bind(context, 0);
		texture1.Bind(context, 1);
		texture2.Bind(context, 2);

		samplerState.Bind(context, 0);

		//context->PSSetShaderResources(0, 1, &texture);
		//context->PSSetShaderResources(1, 1, &texture1);
		//context->PSSetSamplers(0, 1, &samplerState);

		// 드로우 콜 (Draw Call).
		//context->Draw(vertexBuffer.Count(), 0);
		context->DrawIndexed(indexBuffer.Count(), 0u, 0u);
	}
}