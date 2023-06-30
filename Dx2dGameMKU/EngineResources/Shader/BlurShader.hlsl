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
    
    // 화면 전체 범위
    return OutPutValue;
}

//유사하게 따라한 가우시안
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
    //픽셀 하나의 크기
    float2 PixelSize = float2(1.0f / 1280.0f, 1.0f / 720);
    
    // 현재 UV
    float2 PixelUvCenter = _Value.UV.xy;
    
    //블러처리할 왼쪽상단 위치
    float2 StartUV = _Value.UV.xy + (-PixelSize * 2.0f);
    float2 CurUV = StartUV;
    
    float4 ResultColor = (float4) 0.0f;
 
    //왼쪽 상단부터 오른쪽 하단까지 순회
    for (int y = 0; y < 5; ++y)
    {
        for (int x = 0; x < 5; ++x)
        {
            //해당 색상의 Gau[y][x]를 곱한 결과를 전부 더한다
            ResultColor += DiffuseTex.Sample(POINTSAMPLER, CurUV.xy) * Gau[y][x];
            
            //x이동
            CurUV.x += PixelSize.x;
        }
        
        //이동
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