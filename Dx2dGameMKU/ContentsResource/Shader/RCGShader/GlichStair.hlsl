
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

cbuffer GlichData : register(b1)
{
    float Timer;                //0.f += _DelatTime
    float Speed;           //10.f (Speed)
    float Count;           //10.f (파도의 갯수)
    float WaveDiff;     //0.3f(파도들간의 높이 차이)
    
    float MaxWaveHeight;    //1.f
    float GlichRatio;           //0.3f;
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
    return step(0.2f, Rand(floor(_X * _Freq) - floor(_T)));
}




float4 Texture_PS(Output _Value) : SV_Target0
{
    float2 Pos = _Value.UV.xy;
    
    //가로 화면 Count 만큼 분할1
    Pos.x *= Count;
    
    //그 그리드 상의 시작점 X
    float GridPosX = floor(Pos.x);
    //가로 화면 Count 만큼 분할2
    Pos.x = frac(Pos.x);
    
    
    float WaveHeight = Timer * Speed;
    //해당 그리드 상에 대한 파도 높이 설정, sin뒤의 값들은 sin의 치역을 0~1로 바꾸기 위함
    float Height = sin(WaveHeight + GridPosX * WaveDiff) * 0.5f + 0.5f;
    
    //사각형 만들기
    const float RectWidth = 0.9f;
    //중심점이 y가 1이기 때문에 2배를 키웠고, 외부에서 TotalHeight를 통해 파도의 최대 높이를 조절할 수 있다.
    const float RectHeight = (Height * 2.f * MaxWaveHeight);
    float3 Rect = CreateRect(Pos, float2(0.5f, 1.f), float2(RectWidth, RectHeight));
    
    //사각형이 아닌곳은 지우기
    clip(Rect.xyz - 1);
    
    //일정 확률마다 글리치 효과
    if (abs(sin(WaveHeight * (GridPosX + 1.f))) < GlichRatio)
    {
        float Freq = 0.5f;
        float t = 60. + WaveHeight * Freq * 30.;
        
        Freq += Rand(floor(Pos.y));
        const float Offset = 0.9f;
        
        //색상 변경
        Rect.x = RandomSerie(WaveHeight, Freq * 100.f, t + Offset);
        Rect.y = RandomSerie(WaveHeight, Freq * 100.f, t);
        Rect.z = RandomSerie(WaveHeight, Freq * 100.f, t - Offset);
    }
    
    
    return float4(Rect, 1.f);
}



