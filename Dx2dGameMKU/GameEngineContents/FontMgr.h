#pragma once

enum class FontType
{
	Binggrae,
	NanumSquare,
};

class FontMgr
{
public:
	static void Init();
	static void Clear();
	
	inline static const std::string_view& GetFontName(FontType _Type)
	{
		return FontNames[static_cast<size_t>(_Type)];
	}

protected:


private:
	static std::vector<GameEngineFile> FontFiles;
	static std::vector<std::string_view> FontNames;


private:
	FontMgr();
	virtual ~FontMgr() = 0;

	FontMgr(const FontMgr& _Other) = delete;
	FontMgr(FontMgr&& _Other) noexcept = delete;
	FontMgr& operator=(const FontMgr& _Other) = delete;
	FontMgr& operator=(const FontMgr&& _Other) noexcept = delete;
};

