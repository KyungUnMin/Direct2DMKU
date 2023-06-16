//시맨틱 문법
//쉐이더는 그래픽카드에서 처리되기 때문에
//처리할 데이터의 시작위치와 한 버텍스의 크기, 버텍스의 갯수까지 밖에 모른다.
//하지만 그 내부는 모르기 때문에 시맨틱 문법을 이용해 내부를 정의해주어야 한다

//GPU b0레지스터에 저장된 상수버퍼 (슬롯은 0~16까지)
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


//버텍스 쉐이더에서 행렬이 곱해진다
//이때 월드, 뷰, 프로젝션 까지만 곱해지고,
//투영행렬의 w나누기는 하지 않음
//w나누기는 레스터 라이저 단계에서 나눠진다
// 
//output의 SV_Position은
//레스터라이저를 위한 포지션 정보다(w나누기를 하지 않은 값)
//(그러니 필수)
struct Output
{
	//레스터라이제이션을 위해 w에 z값이 남겨진 위치값
	float4 Pos : SV_Position;
    float4 UV : TEXCOORD0;
    float4 ClipUV : TEXCOORD1;
};

cbuffer AtlasData : register(b1)
{
    //이미지를 그릴 UV시작값 ex)0.0, 0.0
    float2 FramePos;
    //이미지의 UV 크기 ex)0.5, 0.5
    float2 FrameScale;
}

cbuffer ClipData : register(b2)
{
    float4 Clip;
}

Output Texture_VS(Input _Value)
{
    Output OutputValue = (Output) 0;

	//여기서 월드, 뷰, w 나누기 전 프로젝션을 곱하게 된다.
    _Value.Pos.w = 1.0f;
    OutputValue.Pos = mul(_Value.Pos, WorldViewProjectionMatrix);
    
    
    //아틀라스 이미지인 경우 AtlasData상수버퍼를 통해 쪼개져서 그려진다
    OutputValue.UV.x = (_Value.UV.x * FrameScale.x) + FramePos.x;
    OutputValue.UV.y = (_Value.UV.y * FrameScale.y) + FramePos.y;

    //클립을 위해 메시 자체의 UV값 전달(0~1), Sprite가 적용되지 않은 온전한 UV값
    OutputValue.ClipUV = _Value.UV;

    return OutputValue;
}

//------------------------------------픽셀 쉐이더---------------

//픽셀 쉐이더는 버텍스 쉐이더에서 만든 결과물들이 래스터라이저 단계를 거쳐서
//이 곳으로 들어온다, 때문에 들어올 때 인자가 버텍스 쉐이더의 나갈 때 인자가 된다

//픽셀 쉐이더에서 사용할 상수버퍼, 버텍스쉐이더와의 슬롯과 상관없다
cbuffer ColorOption : register(b0)
{
    float4 MulColor;
    float4 PlusColor;
}


Texture2D DiffuseTex : register(t0);

//텍스처를 메쉬에 어떻게 매핑할까 라는 규칙을 샘플러라고 한다(색상 결정하는 공식, 옵션)
//UVW 는 각각 XYZ를 의미한다
SamplerState CLAMPSAMPLER : register(s0);


struct OutColor
{
    float4 Color0 : SV_Target0;
    float4 Color1 : SV_Target1;
    float4 Color2 : SV_Target2;
    float4 Color3 : SV_Target3;
};

//픽셀 쉐이더가 끝나면 다음 단계는 아웃풋 머지다.
//그래서 어떤 RTV에 그릴지에 대해 명시해주어야 한다(0번 도화지에 그려라)
float4 Texture_PS(Output _Value) : SV_Target0
{
    //샘플러 설정(0~1사이의 UV값)
    float4 Color = DiffuseTex.Sample(CLAMPSAMPLER, _Value.UV.xy);

    
    if (Clip.z == 0)
    {
        if (_Value.ClipUV.x > Clip.x)
        {
            clip(-1);
        }
    }
    else
    {
        if (_Value.ClipUV.x < 1.0f - Clip.x)
        {
            clip(-1);
        }
    }
    
    if (Clip.w == 0)
    {
        if (_Value.ClipUV.y > Clip.y)
        {
            clip(-1);
        }
    }
    else
    {
        if (_Value.ClipUV.y < 1.0f - Clip.y)
        {
            clip(-1);
        }
    }
    
    
    Color *= MulColor;
    Color += PlusColor;
    
    
    //현재 픽셀을 출력하지 않는 함수
    //if (Color.a == 0)
    //{
    //    clip(-1);
    //}
    
    return Color;
}



