#pragma once


class RCGDefine
{
public:
	RCGDefine(const RCGDefine& _Other) = delete;
	RCGDefine(RCGDefine&& _Other) noexcept = delete;
	RCGDefine& operator=(const RCGDefine& _Other) = delete;
	RCGDefine& operator=(const RCGDefine&& _Other) noexcept = delete;

	static const std::string_view RootPath;
	static const std::string_view ImagePath;
	static const std::string_view ShaderPath;
	static const std::string_view SoundPath;
	static const std::string_view VideoPath;
	
	static const std::string_view EnginePipeName;
	static const std::string_view EngineTexName;

	static const float ResolutionConvertor;

protected:

private:
	RCGDefine();
	virtual ~RCGDefine() = 0;
};





