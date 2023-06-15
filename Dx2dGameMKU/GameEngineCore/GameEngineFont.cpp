#include "PrecompileHeader.h"
#include "GameEngineFont.h"

IFW1Factory* GameEngineFont::Factory = nullptr;

class FontFactoryCreator
{
public:
	FontFactoryCreator()
	{
		//FW1_VERSION : 알아서 Dx버전에 맞춰줌
		FW1CreateFactory(FW1_VERSION, &GameEngineFont::Factory);
	}

	~FontFactoryCreator()
	{
		if (nullptr != GameEngineFont::Factory)
		{
			GameEngineFont::Factory->Release();
			GameEngineFont::Factory = nullptr;
		}
	}
};
FontFactoryCreator InitFont;




GameEngineFont::GameEngineFont()
{

}

GameEngineFont::~GameEngineFont()
{
	if (nullptr != Font)
	{
		Font->Release();
		Font = nullptr;
	}
}



void GameEngineFont::LoadFont(const std::string_view& _Path)
{
	std::wstring WPath = GameEngineString::AnsiToUniCode(_Path.data());

	if (S_OK != GameEngineFont::Factory->CreateFontWrapper(GameEngineDevice::GetDevice(), WPath.c_str(), &Font))
	{
		MsgAssert("폰트 생성 실패");
		return;
	}
}


void GameEngineFont::FontDraw(const std::string_view& _Text)
{
	std::wstring Text = GameEngineString::AnsiToUniCode(_Text);
	float4 Color = { 1.0f, 0.0f, 0.0f, 1.0f };
	Font->DrawString(GameEngineDevice::GetContext(), Text.c_str(), 300.0f, 100.0f, 100.0f, Color.ColorToUint(), FW1_TOP);
}

