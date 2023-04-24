#pragma once

enum class ResType
{
	Image,
	Shader,
	Sound,
	Video
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

	static void MoveContentPath(GameEngineDirectory& _Dir, ResType _Type);

protected:

private:
	RCGDefine();
	virtual ~RCGDefine() = 0;
};





