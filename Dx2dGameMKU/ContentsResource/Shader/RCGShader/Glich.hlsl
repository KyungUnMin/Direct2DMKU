
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
    float Time;
    float Garbage1;
    float Garbage2;
    float Garbage3;
}

float Rand(float _f)
{
    return frac(sin(_f * 4214.124f) * 4124.2457f);
}

float Rand(float2 _v2)
{
    float f = dot(_v2, float2(24.125f, 45.658f));
    return frac(sin(f * 13.2124f) * 75421.4325f);
}

float RandSerie(float _x, float _Freq, float _t)
{
    return step(.8, Rand(floor(_x * _Freq) - floor(_t)));
}


float4 Texture_PS(Output _Value) : SV_Target0
{
    float2 Pos = _Value.UV.xy;
    
    float Cols = 1.f;
    float Freq = Rand(floor(Time)) + abs(atan(Time) * -0.1f);
    float t = 60.f + Time * (1.f - Freq) * 30.f;
    
    if (frac(Pos.y * Cols * 0.5) < 0.5)
    {
        t *= -1.0f;
    }
    
    Freq += Rand(floor(Pos.y));
    
    float Offset = 0.25f;
    
    float3 Color = float3(0.f, 0.f, 0.f);
    Color = float3(
        RandSerie(Pos.x, Freq * 100.f, t + Offset),
        RandSerie(Pos.x, Freq * 100.f, t),
        RandSerie(Pos.x, Freq * 100.f, t - Offset));
    
    
    if (0.f == Color.x && 0.f == Color.y && 0.f == Color.z)
    {
        clip(-1);
    }
    
    return float4(Color, 1.f);
}



