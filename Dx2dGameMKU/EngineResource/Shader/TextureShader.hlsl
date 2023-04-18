//�ø�ƽ ����
//���̴��� �׷���ī�忡�� ó���Ǳ� ������
//ó���� �������� ������ġ�� �� ���ؽ��� ũ��, ���ؽ��� �������� �ۿ� �𸥴�.
//������ �� ���δ� �𸣱� ������ �ø�ƽ ������ �̿��� ���θ� �������־�� �Ѵ�

//GPU b0�������Ϳ� ����� ������� (������ 0~16����)
cbuffer TransformData : register(b0)
{
    float4x4 Worldmatrix;
}

struct Input
{
    float4 Pos : POSITION;
    float4 Color : COLOR;
};


//���ؽ� ���̴����� ����� ��������
//�̶� ����, ��, �������� ������ ��������,
//��������� w������� ���� ����
//w������� ������ ������ �ܰ迡�� ��������
// 
//output�� SV_Position��
//�����Ͷ������� ���� ������ ������(w�����⸦ ���� ���� ��)
//(�׷��� �ʼ�)
struct Output
{
	//�����Ͷ������̼��� ���� w�� z���� ������ ��ġ��
	float4 Pos : SV_Position;
	float4 Color : COLOR;
};

Output Texture_VS(Input _Value)
{
    Output OutputValue = (Output) 0;

	//���⼭ ����, ��, w ������ �� ���������� ���ϰ� �ȴ�.
    _Value.Pos.w = 1.0f;
    OutputValue.Pos = mul(_Value.Pos, Worldmatrix);
    //OutputValue.Pos = _Value.Pos;
    OutputValue.Color = _Value.Color;


    return OutputValue;
}

//------------------------------------�ȼ� ���̴�---------------

//�ȼ� ���̴��� ���ؽ� ���̴����� ���� ��������� �����Ͷ����� �ܰ踦 ���ļ�
//�� ������ ���´�, ������ ���� �� ���ڰ� ���ؽ� ���̴��� ���� �� ���ڰ� �ȴ�

//�ȼ� ���̴����� ����� �������, ���ؽ����̴����� ���԰� �������
cbuffer OutPixelColor : register(b0)
{
    float4 OutColor;
}

//�ȼ� ���̴��� ������ ���� �ܰ�� �ƿ�ǲ ������.
//�׷��� � RTV�� �׸����� ���� ������־�� �Ѵ�(0�� ��ȭ���� �׷���)
float4 Texture_PS(Output _Value) : SV_Target0
{
    return OutColor;
}

