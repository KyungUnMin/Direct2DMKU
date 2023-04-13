
//�ø�ƽ ����
//���̴��� �׷���ī�忡�� ó���Ǳ� ������
//ó���� �������� ������ġ�� �� ���ؽ��� ũ��, ���ؽ��� �������� �ۿ� �𸥴�.
//������ �� ���δ� �𸣱� ������ �ø�ƽ ������ �̿��� ���θ� �������־�� �Ѵ�

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
    OutputValue.Pos = _Value.Pos; /* ���� �� �������� ���ϱ�*/
    OutputValue.Color = _Value.Color;


    return OutputValue;
}

//------------------------------------�ȼ� ���̴�---------------

//�ȼ� ���̴��� ������ ���� �ܰ�� �ƿ�ǲ ������.
//�׷��� � RTV�� �׸����� ���� ������־�� �Ѵ�
struct OutColor
{
	//0�� ��ȭ���� �׷���
    float4 Color : SV_Target0;
};

//�ȼ� ���̴��� ���ؽ� ���̴����� ���� ��������� �����Ͷ����� �ܰ踦 ���ļ�
//�� ������ ���´�, ������ ���� �� ���ڰ� ���ؽ� ���̴��� ���� �� ���ڰ� �ȴ�

OutColor Texture_PS(Output _Value)
{
    OutColor ReturnColor = (OutColor) 0;
    ReturnColor.Color = _Value.Color;
    return ReturnColor;
}