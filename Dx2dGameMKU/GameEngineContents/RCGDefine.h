#pragma once

enum class ResType
{
	Image,
	Shader,
	Sound,
	Video
};

enum class PipeType
{
	DirectColor,
	Burn,
	FieldDoor,
	GlichStair,
	MpBar,
	Tile,
	LevelChangeHeart,
};



class RCGDefine
{
public:
	RCGDefine(const RCGDefine& _Other) = delete;
	RCGDefine(RCGDefine&& _Other) noexcept = delete;
	RCGDefine& operator=(const RCGDefine& _Other) = delete;
	RCGDefine& operator=(const RCGDefine&& _Other) noexcept = delete;

	static const std::string_view EnginePipeName;
	static const std::string_view EngineTexName;

	static const float ResolutionConvertor;
	static const float ResourceScaleConvertor;

	static void MoveContentPath(GameEngineDirectory& _Dir, ResType _Type);
	static void LoadContentPath(ResType _Type, const std::vector<std::string_view>& _Pathes);

	static std::string_view GetPipeName(PipeType _Type)
	{
		return PipeEnumToString[static_cast<size_t>(_Type)];
	}

protected:

private:
	static const std::vector<std::string_view> PipeEnumToString;

	RCGDefine();
	virtual ~RCGDefine() = 0;
};

