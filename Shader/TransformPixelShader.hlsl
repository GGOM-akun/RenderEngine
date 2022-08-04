struct PSInput
{
    float4 position : SV_POSITION;
    float3 color : COLOR;
    float2 texCoord : TEXCOORD;
};

// �ؽ�ó
Texture2D map : register(t0); // register�� �̹��� ���� ������ �����ֹǷ� ������ ������� ��� ���� ����.
Texture2D map1 : register(t1);
Texture2D map2 : register(t2);
SamplerState mapSampler : register(s0);

float4 main(PSInput input) : SV_TARGET
{
	// ���ø�
    float4 mapColor = map.Sample(mapSampler, input.texCoord);
    float4 mapColor1 = map1.Sample(mapSampler, input.texCoord);
    float4 mapColor2 = map2.Sample(mapSampler, input.texCoord);

	// ���� ȥ��(��Ģ���� ����)
    float3 finalColor = (mapColor.rgb * 0.01) + (mapColor1.rgb * 0.01) +
    (mapColor2.rgb * 1) + (input.color * 0.05);
    return float4(finalColor, 1);
}