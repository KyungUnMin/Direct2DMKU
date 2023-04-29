
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

cbuffer TileInfo : register(b0)
{
    float4 Color;
    int XCount;
    int YCount;
    float Thickness;
}

float3 CreateRect(float2 _Pos, float2 _Pivot, float2 _Size)
{
    float2 LeftTop = _Pivot - (_Size / 2.f);
    float2 RightBottom = _Pivot + (_Size / 2.f);

    //(LeftTop <  _Pos) ? 0 : 1
    float2 PCT = step(LeftTop, _Pos);
    //(RightBottom <  _Pos) ? 1 : 0
    PCT -= step(RightBottom, _Pos);

    float ColorValue = PCT.x * PCT.y;
    return float3(ColorValue, ColorValue, 1.f);
}


float4 Texture_PS(Output _Value) : SV_Target0
{
    float2 Pos = _Value.UV.xy;
    
    float Value = XCount * YCount;
    
    Pos.x *= XCount;
    Pos.y *= YCount;
    //Pos %= 1.f;
    Pos = frac(Pos);
    
    const float RectSize = saturate(1.f - Thickness);
    float3 RectArea = CreateRect(Pos, float2(0.5f, 0.5f), float2(RectSize, RectSize));
    if (1.f == RectArea.x)
    {
        clip(-1);
    }
    
    return Color;
}



