cbuffer TransformData : register(b0)
{
    float4 LocalScale;
    float4 LocalRotation;
    float4 LocalQuaternion;
    float4 LocalPosition;
    float4 WorldScale;
    float4 WorldRotation;
    float4 WorldQuaternion;
    float4 WorldPosition;
    float4x4 LocalScaleMatrix;
    float4x4 LocalRotationMatrix;
    float4x4 LocalPositionMatrix;
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

struct OutPut
{
    float4 Pos : SV_Position;
    float4 UV : TEXCOORD;
};


OutPut Texture_VS(Input _Value)
{
    OutPut OutPutValue = (OutPut) 0;
    
    _Value.Pos.w = 1.0f;
    OutPutValue.Pos = mul(_Value.Pos, WorldViewProjectionMatrix);
    OutPutValue.UV = _Value.UV;
    
    return OutPutValue;
}




//-----------------PS------------------

cbuffer CTime : register(b0)
{
    float4 Time;
}

Texture2D DiffuseTex : register(t0);

SamplerState CLAMPSAMPLER : register(s0);


float4 Texture_PS(OutPut _Value) : SV_Target0
{
    float4 PixelData = DiffuseTex.Sample(CLAMPSAMPLER, _Value.UV.xy);
    
    if (0 == PixelData.a)
    {
        clip(-1);
        return PixelData;
    }
    
    float AlphaPercent = abs(cos(Time.x));
    if (_Value.UV.y < (AlphaPercent * 0.5f))
    {
        clip(-1);
        return PixelData;
    }
    
    float Percent = abs(sin(Time.x));
    PixelData.r = clamp(Percent, PixelData.r, 1.f);
    return PixelData;
}



