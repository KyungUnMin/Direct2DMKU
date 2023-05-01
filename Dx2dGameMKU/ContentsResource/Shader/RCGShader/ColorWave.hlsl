
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

cbuffer WaveData : register(b1)
{
    float4 Color;
    float Time;
    float Duration;
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
    
    float TimeRatio = (Time / Duration);
    TimeRatio = frac(TimeRatio);
    
    const float PI2 = 3.141592653589f * 2.f;
    
    //시간에 따라 0.5를 시작으로 1.0f -> 0.f 끝
    float RectRatio = sin(PI2 * TimeRatio) * 0.5f + 0.5f;
    float3 Rect = CreateRect(Pos, float2(0.5f, 1.f), float2(RectRatio, RectRatio * 2.f));
    
    //사각형 밖의 영역 자르기
    clip(Rect.xyz - 1);
    
    float3 ReturnColor;
    ReturnColor = lerp(float3(1.f, 1.f, 1.f), Color.xyz, float3(RectRatio, RectRatio, RectRatio));
    return float4(ReturnColor, TimeRatio);
}
