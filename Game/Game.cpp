#include "Game.h"
#include <Renderer/VertexDeclaration.h>
#include <Utility/TextureLoader.h>
#include <Utility/STLException.h>
#include <Math/MathHelper.h>
#include <cmath>

#include <Device/KeyboardInput.h>

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

		//VertexPositionColorUV vertices[] =
		//{
		//	VertexPositionColorUV({-0.5f,-0.5f, 0.5f}, { 1.0f, 0.0f, 0.0f }, { 0.0f, 1.0f }),		// ���� �ϴ�.
		//	VertexPositionColorUV({-0.5f, 0.5f, 0.5f}, { 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f }),		// ���� ���.
		//	VertexPositionColorUV({ 0.5f, 0.5f, 0.5f}, { 0.0f, 0.0f, 1.0f }, { 1.0f, 0.0f }),		// ������ ���.
		//	VertexPositionColorUV({ 0.5f,-0.5f, 0.5f}, { 1.0f, 1.0f, 1.0f }, { 1.0f, 1.0f }),		// ������ �ϴ�.
		//};

		//vertexBuffer = VertexBuffer(vertices, _countof(vertices), sizeof(vertices[0]));
		//vertexBuffer.Create(device);

		// �ε��� ���� ����.
		//uint32 indices[] = { 0, 1, 3, 1, 2, 3 };

		//indexBuffer = IndexBuffer(indices, _countof(indices));
		//indexBuffer.Create(device);

		// ���̴� �ʱ�ȭ.
		//mainShader.Initialize(device);

		// �Է� ���̾ƿ� ����.
		//LPCSTR SemanticName;
		//UINT SemanticIndex;
		//DXGI_FORMAT Format;
		//UINT InputSlot;
		//UINT AlignedByteOffset;
		//D3D11_INPUT_CLASSIFICATION InputSlotClass;
		//UINT InstanceDataStepRate;
		/*D3D11_INPUT_ELEMENT_DESC layout[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 }
		};*/

		//inputLayout.Create(device, layout, _countof(layout), mainShader.GetVertexShaderBuffer());

		// �ؽ�ó �ε�
		//texture = Texture(L"sample.jpg");
		//texture.Create(device);
		//
		//texture1 = Texture(L"jammin.jpg");
		//texture1.Create(device);
		//
		//texture2 = Texture(L"jammin2.jpg");
		//texture2.Create(device);
		//
		//samplerState.Create(device);

		//// ��ü ����
		//actor1 = std::make_unique<Actor>(device);
		//actor1->Create(device);
		//// X,Y �������� 1/2�� ���
		//actor1->SetScale(0.5f, 0.5f, 1.0f);
		//// ��ü ��ġ�� �������� 0.5��ŭ �̵�
		//actor1->SetPosition(-0.5f, 0.0f, 0.5f);

		//actor2 = std::make_unique<Actor>(device);
		//actor2->Create(device);
		//// X, Y �������� 1/2�� ���
		//actor2->SetScale(0.5f, 0.5f, 1.0f);
		//// ��ü ��ġ�� ���������� 0.5��ŭ �̵�
		//actor2->SetPosition(0.5f, 0.0f, 0.5f);

		//// ��ġ ��ĸ� �����ؼ� ���� ��� ����
		//worldMatrix = Matrix4f::Translation(position);
		//// ���� ����� �����ͷ� ��� ���� ����
		//transformBuffer = ConstantBuffer(&worldMatrix, 1, sizeof(worldMatrix));
		//transformBuffer.Create(device);

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

		// ���� �ʱ�ȭ
		mainLevel.Initialize(device, this);
	}

	void Game::Update(float deltaTime)
	{
		// ���� ������Ʈ
		auto context = deviceManager->GetContext();
		mainLevel.Update(context, deltaTime);

		//// �̵��ڵ�
		//static float alpha = 0.0f;
		//static float sign = 1.0f;
		//static float moveSpeed = 0.5;
		//static float actorOffset = actor1->Position().y;
		//static float actorOffset2 = actor2->Position().x;
		//alpha += moveSpeed * deltaTime * sign * sin(gameTimer->TotalTime());	// sin(gameTimer->TotalTime()�� �����ָ� �ӵ��� ����.
		//if (deltaTime > 1.0f)
		//{
		//	alpha = 0.0f;
		//}
		//
		//if (alpha > 1.0f)
		//{
		//	sign = -1.0f;
		//}
		//
		//if (alpha < 0.0f)
		//{
		//	sign = 1.0f;
		//}
		//
		//static float yStart = -0.25f;
		//static float yEnd = -0.75f;
		//
		//static float xStart = -0.25f;
		//static float xEnd = 0.25f;
		//
		//float yPosition = MathHelper::Lerpf(yStart, yEnd, alpha);
		//actor1->SetPosition(yPosition + actorOffset, 0.0f, 0.0f);
		////actor2->SetPosition(xPosition + actorOffset2, 0.0f, 0.0f);
		//
		//float xPosition = MathHelper::Lerpf(xStart, xEnd, alpha);
		////actor1->SetPosition(xPosition + actorOffset, 0.0f, 0.0f);
		//actor2->SetPosition(xPosition + actorOffset2, 0.0f, 0.0f);
		//
		//auto context = deviceManager->GetContext();
		//actor1->Update(context, deltaTime);
		//actor2->Update(context, deltaTime);
	}
	
	void Game::RenderScene()
	{
		auto context = deviceManager->GetContext();

		// Draw �Լ��� �����ϱ� ���� GPU���� ����� ���ҽ��� ��� ���ε�(����)�Ѵ�.
		// ������ ��� ����.
		//inputLayout.Bind(context);
		//vertexBuffer.Bind(context);
		//mainShader.Bind(context);
		//
		//indexBuffer.Bind(context);
		//
		//texture.Bind(context, 0);
		//texture1.Bind(context, 1);
		//texture2.Bind(context, 2);
		//
		//samplerState.Bind(context, 0);

		mainLevel.Bind(context);
		mainLevel.Draw(context);

		//actor1->Bind(context);
		//
		//context->PSSetShaderResources(0, 1, &texture);
		//context->PSSetShaderResources(1, 1, &texture1);
		//context->PSSetSamplers(0, 1, &samplerState);
		//
		// ��ο� �� (Draw Call).
		//context->Draw(vertexBuffer.Count(), 0);
		//context->DrawIndexed(indexBuffer.Count(), 0u, 0u);
		//
		//actor2->Bind(context);
		//
		//context->DrawIndexed(indexBuffer.Count(), 0u, 0u);
	}

	void Game::ProcessInput()
	{
		Application::ProcessInput();

		// ESC Ű ���� ó��
		if (keyboard->IsKeyDown(Keys::Escape))
		{
			if (MessageBox(nullptr, L"���� �Ͻðڽ��ϱ�?", L"����", MB_YESNO)
				== IDYES)
			{
				DestroyWindow(mainWindow->Handle());
			}
		}
	}
}