#include "Game.h"
#include <Renderer/VertexDeclaration.h>
#include <Utility/TextureLoader.h>
#include <Utility/STLException.h>
#include <Math/MathHelper.h>

namespace STL
{
	Game::Game(HINSTANCE hInstance, uint32 width, uint32 height, const std::wstring& title)
		: Application(hInstance, width, height, title)
	{
	}

	Game::~Game()
	{
		// �ε��� �ؽ�ó ���ҽ� ����
		TextureLoader::Release();
	}
	
	void Game::Initialize()
	{
		Application::Initialize();

		// ��ġ ���� ����.
		auto device = deviceManager->GetDevice();

		// ���� ���� ����.

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

		//	VertexPosition(-0.5f,-0.5f, 0.5f),		// ���� �ϴ�.
		//	VertexPosition(-0.5f, 0.5f, 0.5f),		// ���� ���.
		//	VertexPosition( 0.5f, 0.5f, 0.5f),		// ������ ���.
		//	VertexPosition( 0.5f,-0.5f, 0.5f),		// ������ �ϴ�.
		//};

		//VertexPositionColor vertices[] =
		//{
		//	VertexPositionColor({-0.5f,-0.5f, 0.5f}, { 1.0f, 0.0f, 0.0f }),		// ���� �ϴ�.
		//	VertexPositionColor({-0.5f, 0.5f, 0.5f}, { 0.0f, 1.0f, 0.0f }),		// ���� ���.
		//	VertexPositionColor({ 0.5f, 0.5f, 0.5f}, { 0.0f, 0.0f, 1.0f }),		// ������ ���.
		//	VertexPositionColor({ 0.5f,-0.5f, 0.5f}, { 1.0f, 0.0f, 0.0f }),		// ������ �ϴ�.
		//};

		VertexPositionColorUV vertices[] =
		{
			VertexPositionColorUV({-0.5f,-0.5f, 0.5f}, { 1.0f, 0.0f, 0.0f }, { 0.0f, 1.0f }),		// ���� �ϴ�.
			VertexPositionColorUV({-0.5f, 0.5f, 0.5f}, { 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f }),		// ���� ���.
			VertexPositionColorUV({ 0.5f, 0.5f, 0.5f}, { 0.0f, 0.0f, 1.0f }, { 1.0f, 0.0f }),		// ������ ���.
			VertexPositionColorUV({ 0.5f,-0.5f, 0.5f}, { 1.0f, 1.0f, 1.0f }, { 1.0f, 1.0f }),		// ������ �ϴ�.
		};

		vertexBuffer = VertexBuffer(vertices, _countof(vertices), sizeof(vertices[0]));
		vertexBuffer.Create(device);

		// �ε��� ���� ����.
		uint32 indices[] = { 0, 1, 3, 1, 2, 3 };

		indexBuffer = IndexBuffer(indices, _countof(indices));
		indexBuffer.Create(device);

		// ���̴� �ʱ�ȭ.
		mainShader.Initialize(device);

		// �Է� ���̾ƿ� ����.
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

		// �ؽ�ó �ε�
		texture = Texture(L"sample.jpg");
		texture.Create(device);

		texture1 = Texture(L"jammin.jpg");
		texture1.Create(device);

		texture2 = Texture(L"jammin2.jpg");
		texture2.Create(device);

		samplerState.Create(device);

		// ��ġ ��ĸ� �����ؼ� ���� ��� ����
		worldMatrix = Matrix4f::Translation(position);
		// ���� ����� �����ͷ� ��� ���� ����
		transformBuffer = ConstantBuffer(&worldMatrix, 1, sizeof(worldMatrix));
		transformBuffer.Create(device);

		//rotation.z = 180.0f;
		//scale.x = 0.5f;
		//position.y = 0.5f;

		//// ���÷� ������Ʈ ����
		//D3D11_SAMPLER_DESC samplerDesc = {};
		//samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		//samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
		//samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
		//samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;

		//auto result = device->CreateSamplerState(&samplerDesc, &samplerState);
		//ThrowIfFailed(result, "failed to create sampler state");
	}

	void Game::Update(float deltaTime)
	{
		static float alpha = 0.0f;
		static float sign = 1.0f;
		alpha += 0.5f * deltaTime * sign;
		if (deltaTime > 1.0f)
		{
			alpha = 0.0f;
		}

		if (alpha > 1.0f)
		{
			sign = -1.0f;
		}

		if (alpha < 0.0f)
		{
			sign = 1.0f;
		}

		static float xStart = -0.5f;
		static float xEnd = 0.5f;

		float xPosition = MathHelper::Lerpf(xStart, xEnd, alpha);
		position.x = xPosition;

		// ��ġ/ȸ��/������ ���� �����ؼ� ���� ��� ������ ������Ʈ
		worldMatrix = Matrix4f::Scale(scale)
			* Matrix4f::Rotation(rotation)
			* Matrix4f::Translation(position);

		// ���ŵ� ���� ��� �����ͷ� ��� ���� ������Ʈ
		transformBuffer.Update(deviceManager->GetContext(), &worldMatrix);
	}
	
	void Game::RenderScene()
	{
		auto context = deviceManager->GetContext();

		// Draw �Լ��� �����ϱ� ���� GPU���� ����� ���ҽ��� ��� ���ε�(����)�Ѵ�.
		// ������ ��� ����.
		inputLayout.Bind(context);
		vertexBuffer.Bind(context);
		mainShader.Bind(context);

		indexBuffer.Bind(context);

		texture.Bind(context, 0);
		texture1.Bind(context, 1);
		texture2.Bind(context, 2);

		samplerState.Bind(context, 0);

		transformBuffer.Bind(context, 0);

		//context->PSSetShaderResources(0, 1, &texture);
		//context->PSSetShaderResources(1, 1, &texture1);
		//context->PSSetSamplers(0, 1, &samplerState);

		// ��ο� �� (Draw Call).
		//context->Draw(vertexBuffer.Count(), 0);
		context->DrawIndexed(indexBuffer.Count(), 0u, 0u);
	}
}