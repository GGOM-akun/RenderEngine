struct PSInput
{
	float4 position : SV_POSITION;
	float3 color : COLOR;
	float2 texCoord : TEXCOORD;
};

// 텍스처
Texture2D map : register(t0);		// register는 이미지 파일 순서를 정해주므로 순서가 상관없는 경우 생략 가능.
SamplerState mapSampler : register(s0);

float4 main(PSInput input) : SV_TARGET
{
	// 샘플링
	float4 mapColor = map.Sample(mapSampler, input.texCoord);

	return mapColor;
}