
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

//------------------------------------«»ºø Ω¶¿Ã¥ı---------------

cbuffer MpRatio : register(b0)
{
    float4 Ratio;
}


Texture2D DiffuseTex : register(t0);
SamplerState CLAMPSAMPLER : register(s0);

float4 Texture_PS(Output _Value) : SV_Target0
{
    if (0.f == Ratio.x)
    {
        return float4(0.f, 0.f, 0.f, 0.f);
    }
    
    float4 Color = DiffuseTex.Sample(CLAMPSAMPLER, _Value.UV.xy);
    
    if (Ratio.x < _Value.UV.x)
    {
        Color.w = 0.f;
    }
 
    return Color;
}



