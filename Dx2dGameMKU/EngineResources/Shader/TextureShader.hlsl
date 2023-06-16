//�ø�ƽ ����
//���̴��� �׷���ī�忡�� ó���Ǳ� ������
//ó���� �������� ������ġ�� �� ���ؽ��� ũ��, ���ؽ��� �������� �ۿ� �𸥴�.
//������ �� ���δ� �𸣱� ������ �ø�ƽ ������ �̿��� ���θ� �������־�� �Ѵ�

//GPU b0�������Ϳ� ����� ������� (������ 0~16����)
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
    float4 UV : TEXCOORD0;
    float4 ClipUV : TEXCOORD1;
};

cbuffer AtlasData : register(b1)
{
    //�̹����� �׸� UV���۰� ex)0.0, 0.0
    float2 FramePos;
    //�̹����� UV ũ�� ex)0.5, 0.5
    float2 FrameScale;
}

cbuffer ClipData : register(b2)
{
    float4 Clip;
}

Output Texture_VS(Input _Value)
{
    Output OutputValue = (Output) 0;

	//���⼭ ����, ��, w ������ �� ���������� ���ϰ� �ȴ�.
    _Value.Pos.w = 1.0f;
    OutputValue.Pos = mul(_Value.Pos, WorldViewProjectionMatrix);
    
    
    //��Ʋ�� �̹����� ��� AtlasData������۸� ���� �ɰ����� �׷�����
    OutputValue.UV.x = (_Value.UV.x * FrameScale.x) + FramePos.x;
    OutputValue.UV.y = (_Value.UV.y * FrameScale.y) + FramePos.y;

    //Ŭ���� ���� �޽� ��ü�� UV�� ����(0~1), Sprite�� ������� ���� ������ UV��
    OutputValue.ClipUV = _Value.UV;

    return OutputValue;
}

//------------------------------------�ȼ� ���̴�---------------

//�ȼ� ���̴��� ���ؽ� ���̴����� ���� ��������� �����Ͷ����� �ܰ踦 ���ļ�
//�� ������ ���´�, ������ ���� �� ���ڰ� ���ؽ� ���̴��� ���� �� ���ڰ� �ȴ�

//�ȼ� ���̴����� ����� �������, ���ؽ����̴����� ���԰� �������
cbuffer ColorOption : register(b0)
{
    float4 MulColor;
    float4 PlusColor;
}


Texture2D DiffuseTex : register(t0);

//�ؽ�ó�� �޽��� ��� �����ұ� ��� ��Ģ�� ���÷���� �Ѵ�(���� �����ϴ� ����, �ɼ�)
//UVW �� ���� XYZ�� �ǹ��Ѵ�
SamplerState CLAMPSAMPLER : register(s0);


struct OutColor
{
    float4 Color0 : SV_Target0;
    float4 Color1 : SV_Target1;
    float4 Color2 : SV_Target2;
    float4 Color3 : SV_Target3;
};

//�ȼ� ���̴��� ������ ���� �ܰ�� �ƿ�ǲ ������.
//�׷��� � RTV�� �׸����� ���� ������־�� �Ѵ�(0�� ��ȭ���� �׷���)
float4 Texture_PS(Output _Value) : SV_Target0
{
    //���÷� ����(0~1������ UV��)
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
    
    
    //���� �ȼ��� ������� �ʴ� �Լ�
    //if (Color.a == 0)
    //{
    //    clip(-1);
    //}
    
    return Color;
}



