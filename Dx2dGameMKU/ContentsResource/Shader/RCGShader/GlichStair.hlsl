
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

cbuffer GlichData : register(b1)
{
    float WaveHeight; //Speed * _DelatTime
    float Count;           //10.f
    float WaveDiff;     //0.5f
    float GlichFrequence; //???
}

float Rand(float _f)
{
    return frac(sin(_f) * 1e4);
}

float Rand(float2 _v2)
{
    return frac(sin(dot(_v2.xy, float2(12.9898f, 78.233f))) * 43758.5453123f);
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



float RandomSerie(float _X, float _Freq, float _T)
{
    return step(0.8f, Rand(floor(_X * _Freq) - floor(_T)));
}




float4 Texture_PS(Output _Value) : SV_Target0
{
    float2 Pos = _Value.UV.xy;
    Pos.x *= Count;
    
    float GridPosX = floor(Pos.x);
    Pos.x = frac(Pos.x);
    
    
    float Height = sin(WaveHeight + GridPosX * WaveDiff) * 0.5f + 0.5f;
    
    const float RectWidth = 0.9f;
    float3 Rect = CreateRect(Pos, float2(0.5f, 1.f), float2(RectWidth, Height * 2.f));
    
    clip(Rect.xyz - 1);
    
    if (abs(sin(WaveHeight * (GridPosX + 1.f))) < 0.5f)
    {
        float Freq = 0.5f;
        float t = 60. + WaveHeight * Freq * 30.;
        
        Freq += Rand(floor(Pos.y));
        const float Offset = 0.3f;
        
        Rect.x = RandomSerie(WaveHeight, Freq * 100.f, t + Offset);
        Rect.y = RandomSerie(WaveHeight, Freq * 100.f, t);
        Rect.z = RandomSerie(WaveHeight, Freq * 100.f, t - Offset);
    }
    
    return float4(Rect, 1.f);
}



