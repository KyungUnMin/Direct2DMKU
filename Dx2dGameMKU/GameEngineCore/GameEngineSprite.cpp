#include "PrecompileHeader.h"
#include "GameEngineSprite.h"

GameEngineSprite::GameEngineSprite()
{

}

GameEngineSprite::~GameEngineSprite()
{

}

void GameEngineSprite::ResLoadFolder(const std::string_view& _Path)
{
	GameEngineDirectory Dir = _Path;

	if (false == Dir.GetPath().IsDirectory())
	{
		MsgAssert("���丮�� �ƴ� ����Դϴ�. : \n" + std::string(_Path));
	}

	std::vector<GameEngineFile> AllFile = Dir.GetAllFile({ ".png", ".jpg" });

	if (true == AllFile.empty())
	{
		MsgAssert("�̹����� �������� �ʴ� ����Դϴ�. : \n" + std::string(_Path));
	}

	//������
	std::string FileName = Dir.GetPath().GetFileName();

	//��ο� �ִ� �ؽ�ó ��� �ε��� �� Sprites���Ϳ� ���
	Sprites.resize(AllFile.size());
	for (size_t i = 0; i < AllFile.size(); ++i)
	{
		GameEngineFile& File = AllFile[i];
		std::shared_ptr<GameEngineTexture> Texture = GameEngineTexture::Load(File.GetFullPath());

		Sprites[i].Texture = Texture;
		Sprites[i].CutData.PosX = 0.0f;
		Sprites[i].CutData.PosY = 0.0f;
		Sprites[i].CutData.SizeX = 1.0f;
		Sprites[i].CutData.SizeY = 1.0f;
	}
}



void GameEngineSprite::ResLoadSheet(const std::string_view& _Path, size_t _X, size_t _Y)
{
	GameEnginePath NewPath(_Path);

	//�ؽ�ó�� �ε���� �ʾҴٸ� �ε�
	std::shared_ptr<GameEngineTexture> Texture = GameEngineTexture::Find(NewPath.GetFileName());
	if (nullptr == Texture)
	{
		Texture = GameEngineTexture::Load(_Path);
	}

	Sprites.resize(_X * _Y);
	const float4 UVScale = float4{ 1.0f / static_cast<float>(_X), 1.0f / static_cast<float>(_Y) };
	float4 Start = float4::Zero;

	for (size_t y = 0; y < _Y; ++y)
	{
		for (size_t x = 0; x < _X; ++x)
		{
			size_t Index = (_X * y) + x;

			Sprites[Index].Texture = Texture;
			Sprites[Index].CutData.PosX = Start.x;
			Sprites[Index].CutData.PosY = Start.y;
			Sprites[Index].CutData.SizeX = UVScale.x;
			Sprites[Index].CutData.SizeY = UVScale.y;
			Start.x += UVScale.x;
		}

		Start.x += 0.0f;
		Start.y += UVScale.y;
	}
}
