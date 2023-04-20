//�ø�ƽ ����
//���̴��� �׷���ī�忡�� ó���Ǳ� ������
//ó���� �������� ������ġ�� �� ���ؽ��� ũ��, ���ؽ��� �������� �ۿ� �𸥴�.
//������ �� ���δ� �𸣱� ������ �ø�ƽ ������ �̿��� ���θ� �������־�� �Ѵ�

//GPU b0�������Ϳ� ����� ������� (������ 0~16����)
cbuffer TransformData : register(b0)
{
    float4 LocalScale;
    float4 LocalRotation;
    float4 LocalQuaternion;
    float4 LocalPosition;
    float4 WorldScale;
    float4 WorldRotation;
    float4 WorldQuaternion;
    float4 WorldPosition;
    float4x4 LocalScaleMatrix;
    float4x4 LocalRotationMatrix;
    float4x4 LocalPositionMatrix;
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
    float4 UV : TEXCOORD;
};

Output Texture_VS(Input _Value)
{
    Output OutputValue = (Output) 0;

	//���⼭ ����, ��, w ������ �� ���������� ���ϰ� �ȴ�.
    _Value.Pos.w = 1.0f;
    OutputValue.Pos = mul(_Value.Pos, WorldViewProjectionMatrix);
    //OutputValue.Pos = _Value.Pos;
    OutputValue.UV = _Value.UV;


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


Texture2D DiffuseTex : register(t0);

//�ؽ�ó�� �޽��� ��� �����ұ� ��� ��Ģ�� ���÷���� �Ѵ�(���� �����ϴ� ����, �ɼ�)
//UVW �� ���� XYZ�� �ǹ��Ѵ�
SamplerState CLAMPSAMPLER : register(s0);

//�ȼ� ���̴��� ������ ���� �ܰ�� �ƿ�ǲ ������.
//�׷��� � RTV�� �׸����� ���� ������־�� �Ѵ�(0�� ��ȭ���� �׷���)
float4 Texture_PS(Output _Value) : SV_Target0
{
    //���÷� ����(0~1������ UV��)
    float4 Color = DiffuseTex.Sample(CLAMPSAMPLER, _Value.UV.xy);

    //���� �ȼ��� ������� �ʴ� �Լ�
     //if (0.5 < _Value.Color.x)
    //{
    //    clip(-1);
    //}
    
    return Color;
}



