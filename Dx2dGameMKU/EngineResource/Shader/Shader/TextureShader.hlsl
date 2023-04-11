
//시맨틱 문법
//쉐이더는 그래픽카드에서 처리되기 때문에
//처리할 데이터의 시작위치와 한 버텍스의 크기, 버텍스의 갯수까지 밖에 모른다.
//하지만 그 내부는 모르기 때문에 시맨틱 문법을 이용해 내부를 정의해주어야 한다

struct MyInput
{
	float4 Pos : POSITION0;
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
struct MyOutput
{
	//레스터라이제이션을 위해 w에 z값이 남겨진 위치값
	float4 Pos : SV_Position;
	float4 Color : COLOR;
};

MyOutput Texture_VS(MyInput _Value)
{
	MyOutput OutputValue = (MyOutput)0;

	//여기서 월드, 뷰, w 나누기 전 프로젝션을 곱하게 된다.
	OutputValue.Pos = _Value.Pos; /* 월드 뷰 프로젝션 곱하기*/
	OutputValue.Color = _Value.Color;


	return OutputValue;
}