
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

//------------------------------------픽셀 쉐이더---------------

cbuffer BloomData : register(b0)
{
    float4 LightColor; //
    float RimRange; //1~10
    //float Intensity; //?
}


Texture2D DiffuseTex : register(t0);
SamplerState CLAMPSAMPLER : register(s0);


float4 Texture_PS(Output _Value) : SV_Target0
{
    float4 UVColor = DiffuseTex.Sample(CLAMPSAMPLER, _Value.UV.xy);
    if (0.f == UVColor.a)
    {
        clip(-1);
        //return float4(0.f, 0.f, 0.f, 0.f);
    }
    
    //원점을 중심점으로 이동
    float2 Coord = _Value.UV.xy * 2.f - 1.f;
    
    ////중심점으로부터 이 픽셀까지의 벡터의 길이
    float Size = distance(Coord.xy, float2(0.0f, 0.0f));
    //float BloomAlpha = pow(1.f - Size, RimRange);
    //float BloomAlpha = (Size / RimRange);

    //return float4(LightColor.xyz, Size);
    return float4(LightColor.xyz, Size);
}



