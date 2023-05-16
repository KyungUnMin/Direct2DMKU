
cbuffer TransformData : register(b0)
{
    float4 Scale;
    float4 Rotation;
    float4 Quaternion;
    float4 Position;

    float4 LocalScale;
    float4 LocalRotation;
    float4 LocalQuaternion;
    float4 LocalPosition;

    float4 WorldScale;
    float4 WorldRotation;
    float4 WorldQuaternion;
    float4 WorldPosition;

    float4x4 ScaleMatrix;
    float4x4 RotationMatrix;
    float4x4 PositionMatrix;
    float4x4 LocalWorldMatrix;
    float4x4 WorldMatrix;
    float4x4 View;
    float4x4 Projection;
    float4x4 ViewPort;
    float4x4 WorldViewProjectionMatrix;
}

struct Input
{
    float4 Pos : POSITION;
    float4 UV : TEXCOORD;
};


struct Output
{
    float4 Pos : SV_Position;
    float4 UV : TEXCOORD;
};

Output Texture_VS(Input _Value)
{
    Output OutputValue = (Output) 0;

    _Value.Pos.w = 1.0f;
    OutputValue.Pos = mul(_Value.Pos, WorldViewProjectionMatrix);
    OutputValue.UV = _Value.UV;

    return OutputValue;
}

//------------------------------------�ȼ� ���̴�---------------

cbuffer NoiseFilter : register(b0)
{
    float4 FireColor;
    float Ratio;            //0~1
    float NoiseSize;    //5.f
    float OffsetRatio;
}


Texture2D DiffuseTex : register(t0);
SamplerState CLAMPSAMPLER : register(s0);


float2 Rand(float2 _Value)
{
    float f1 = dot(_Value, float2(56.37f, 67.531f));
    float f2 = dot(_Value, float2(69.08641f, 75.3739f));

    float x = frac(sin(f1 * 6.7876f) * 156423.12312f);
    float y = frac(cos(f2 * 1.34531f) * 163451.12512f);
 
    //������ -1 ~ 1�� ����(frac�� ���� ������ 0~ 1�����̱� ����)
    return float2(x, y) * 2.f - 1.f;
}

float Noise(float2 _Vec)
{
    //������ �Ǽ� �̾Ƴ���
    float2 Integer0 = floor(_Vec);
    float2 Real= frac(_Vec);

    //�ش� �׸����� �� �𼭸� ��ġ
    float2 Integer1 = Integer0 + float2(1.f, 0.f);
    float2 Integer2 = Integer0 + float2(0.f, 1.f);
    float2 Integer3 = Integer0 + float2(1.f, 1.f);

    //�׸��� �� �𼭸��� ���� ���� ���� ����
    float2 R0 = Rand(Integer0);
    float2 R1 = Rand(Integer1);
    float2 R2 = Rand(Integer2);
    float2 R3 = Rand(Integer3);

    //Real = smoothstep(0.f, 1.f, Real);
    Real = Real * Real * Real * (Real * (Real * 6.0f - 15.f) + 10.f);

    //�׸��� �߾Ӱ� �� �𼭸��� ��ġ�� ���͵��� ����
    float D0 = dot(R0, _Vec - Integer0);
    float D1 = dot(R1, _Vec - Integer1);
    float D2 = dot(R2, _Vec - Integer2);
    float D3 = dot(R3, _Vec - Integer3);

    float Bottom = lerp(D0, D1, Real.x);
    float Top = lerp(D2, D3, Real.x);
    float ReturnValue = lerp(Bottom, Top, Real.y);
    
    return ReturnValue * 0.5f + 0.5f;
}


float4 Texture_PS(Output _Value) : SV_Target0
{
    float4 Color = DiffuseTex.Sample(CLAMPSAMPLER, _Value.UV.xy);
    if (0.f == Color.w)
    {
        clip(-1);
    }
    
    float2 Pos = _Value.UV.xy;
    Pos *= NoiseSize;

    float NoiseValue = Noise(Pos);
    
    if (Ratio < NoiseValue)
    {
        clip(-1);
    }
    else if (Ratio < (NoiseValue + OffsetRatio))
    {
        return FireColor;
    }
    
    //�Ҳ��� �Ϸ��̴� ������ ���߿� å ���� �ٽ� �غ���
    
    return Color;
}



