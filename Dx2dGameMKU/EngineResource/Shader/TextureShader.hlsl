
//�ø�ƽ ����
//���̴��� �׷���ī�忡�� ó���Ǳ� ������
//ó���� �������� ������ġ�� �� ���ؽ��� ũ��, ���ؽ��� �������� �ۿ� �𸥴�.
//������ �� ���δ� �𸣱� ������ �ø�ƽ ������ �̿��� ���θ� �������־�� �Ѵ�

struct MyInput
{
	float4 Pos : POSITION0;
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
struct MyOutput
{
	//�����Ͷ������̼��� ���� w�� z���� ������ ��ġ��
	float4 Pos : SV_Position;
	float4 Color : COLOR;
};

MyOutput Texture_VS(MyInput _Value)
{
	MyOutput OutputValue = (MyOutput)0;

	//���⼭ ����, ��, w ������ �� ���������� ���ϰ� �ȴ�.
	OutputValue.Pos = _Value.Pos; /* ���� �� �������� ���ϱ�*/
	OutputValue.Color = _Value.Color;


	return OutputValue;
}