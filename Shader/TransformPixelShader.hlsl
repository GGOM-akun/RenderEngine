struct PSInput
{
    float4 position : SV_POSITION;
    float3 color : COLOR;
    float2 texCoord : TEXCOORD;
};

// 텍스처
Texture2D map : register(t0); // register는 이미지 파일 순서를 정해주므로 순서가 상관없는 경우 생략 가능.
Texture2D map1 : register(t1);
Texture2D map2 : register(t2);
SamplerState mapSampler : register(s0);

float4 main(PSInput input) : SV_TARGET
{
	// 샘플링
    float4 mapColor = map.Sample(mapSampler, input.texCoord);
    float4 mapColor1 = map1.Sample(mapSampler, input.texCoord);
    float4 mapColor2 = map2.Sample(mapSampler, input.texCoord);

	// 색상 혼합(사칙연산 가능)
    float3 finalColor = (mapColor.rgb * 0.01) + (mapColor1.rgb * 0.01) +
    (mapColor2.rgb * 1) + (input.color * 0.05);
    return float4(finalColor, 1);
}