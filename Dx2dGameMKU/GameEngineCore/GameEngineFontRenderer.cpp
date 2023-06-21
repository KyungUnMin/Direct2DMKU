#include "PrecompileHeader.h"
#include "GameEngineFontRenderer.h"


GameEngineFontRenderer::GameEngineFontRenderer()
{

}

GameEngineFontRenderer::~GameEngineFontRenderer()
{

}

void GameEngineFontRenderer::SetFont(const std::string_view& _Font)
{
	Font = GameEngineFont::Find(_Font);
}

void GameEngineFontRenderer::SetText(const std::string_view& _Text)
{
	Text = _Text;
}



void GameEngineFontRenderer::Render(float _DeltaTime)
{
	if (nullptr == Font)
	{
		return;
	}

	if ("" == Text)
	{
		return;
	}

	

	//�� �������� ���� ��ġ��
	float4 Pos = GetTransform()->GetWorldPosition();
	GameEngineCamera* Camera = GetCamera();

	//�� �������� ����Ʈ�� ���ؼ� ������ ��ǥ�� �����
	Pos *= Camera->GetView();
	Pos *= Camera->GetProjection();
	Pos *= Camera->GetViewPort();

	Font->FontDraw(Text, Pos, FontScale, FontColor, FwTextFlag);


	//������������ �ٸ� �������� ������ ������ ��� �����ִ´�
	//��Ʈ���۴� ������Ʈ�� ���̴��� ����Ѵ�
	// 
	// ������Ʈ���� ���ؽ� ���̴��� ������ �Է¹޾ƾ� �Ѵ�
	// �� ���ؽ��ʿ��� ������ �ǳ����� ������ ������ �߻��Ѵ�
	// 
	// �� ��Ʈ �������� ������ ������
	// �ٸ� �������� �������� �����Ҷ���
	// ������ ������Ʈ�� ���̴��� �����ִ�
	//�׷��� ������ �����ϱ� ���� ������ ������Ʈ�����̴��� ���������� ���ش�
	GameEngineDevice::GetContext()->GSSetShader(nullptr, nullptr, 0);
}


void GameEngineFontRenderer::Start()
{
	GameEngineRenderer::Start();
}