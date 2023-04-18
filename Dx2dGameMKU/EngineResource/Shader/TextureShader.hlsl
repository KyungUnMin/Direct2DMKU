//시맨틱 문법
//쉐이더는 그래픽카드에서 처리되기 때문에
//처리할 데이터의 시작위치와 한 버텍스의 크기, 버텍스의 갯수까지 밖에 모른다.
//하지만 그 내부는 모르기 때문에 시맨틱 문법을 이용해 내부를 정의해주어야 한다

//GPU b0레지스터에 저장된 상수버퍼 (슬롯은 0~16까지)
cbuffer TransformData : register(b0)
{
    float4x4 Worldmatrix;
}

struct Input
{
    float4 Pos : POSITION;
    float4 Color : COLOR;
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
	float4 Color : COLOR;
};

Output Texture_VS(Input _Value)
{
    Output OutputValue = (Output) 0;

	//여기서 월드, 뷰, w 나누기 전 프로젝션을 곱하게 된다.
    _Value.Pos.w = 1.0f;
    OutputValue.Pos = mul(_Value.Pos, Worldmatrix);
    //OutputValue.Pos = _Value.Pos;
    OutputValue.Color = _Value.Color;


    return OutputValue;
}

//------------------------------------픽셀 쉐이더---------------

//픽셀 쉐이더는 버텍스 쉐이더에서 만든 결과물들이 래스터라이저 단계를 거쳐서
//이 곳으로 들어온다, 때문에 들어올 때 인자가 버텍스 쉐이더의 나갈 때 인자가 된다

//픽셀 쉐이더에서 사용할 상수버퍼, 버텍스쉐이더와의 슬롯과 상관없다
cbuffer OutPixelColor : register(b0)
{
    float4 OutColor;
}

//픽셀 쉐이더가 끝나면 다음 단계는 아웃풋 머지다.
//그래서 어떤 RTV에 그릴지에 대해 명시해주어야 한다(0번 도화지에 그려라)
float4 Texture_PS(Output _Value) : SV_Target0
{
    return OutColor;
}

