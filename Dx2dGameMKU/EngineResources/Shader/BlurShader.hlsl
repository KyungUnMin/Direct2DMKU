struct Input
{
    float4 Pos : POSITION;
    float4 UV : TEXCOORD;
};

struct OutPut
{
    float4 Pos : SV_Position;
    float4 UV : TEXCOORD;
};

OutPut Blur_VS(Input _Value)
{
    OutPut OutPutValue = (OutPut) 0;
    OutPutValue.Pos = _Value.Pos;
    OutPutValue.UV = _Value.UV;
    
    // ȭ�� ��ü ����
    return OutPutValue;
}

//�����ϰ� ������ ����þ�
static float Gau[5][5] =
{
    { 1, 4, 6, 4, 1 },
    { 4, 16, 24, 16, 4 },
    { 6, 24, 36, 24, 6 },
    { 4, 16, 24, 16, 4 },
    { 1, 4, 6, 4, 1 }
};

Texture2D DiffuseTex : register(t0);
SamplerState POINTSAMPLER : register(s0);

float4 Blur_PS(OutPut _Value) : SV_Target0
{
    //�ȼ� �ϳ��� ũ��
    float2 PixelSize = float2(1.0f / 1280.0f, 1.0f / 720);
    
    // ���� UV
    float2 PixelUvCenter = _Value.UV.xy;
    
    //��ó���� ���ʻ�� ��ġ
    float2 StartUV = _Value.UV.xy + (-PixelSize * 2.0f);
    float2 CurUV = StartUV;
    
    float4 ResultColor = (float4) 0.0f;
 
    //���� ��ܺ��� ������ �ϴܱ��� ��ȸ
    for (int y = 0; y < 5; ++y)
    {
        for (int x = 0; x < 5; ++x)
        {
            //�ش� ������ Gau[y][x]�� ���� ����� ���� ���Ѵ�
            ResultColor += DiffuseTex.Sample(POINTSAMPLER, CurUV.xy) * Gau[y][x];
            
            //x�̵�
            CurUV.x += PixelSize.x;
        }
        
        //�̵�
        CurUV.x = StartUV.x;
        CurUV.y += PixelSize.y;
    }
    
    ResultColor /= 256.0f;
    
    if (ResultColor.a <= 0.0f)
    {
        clip(-1);
    }
    
    return ResultColor;
}