#pragma once

enum class KeyNames
{
	UpArrow,
	DownArrow,
	RightArrow,
	LeftArrow,
	Space,

	Esc,
	DebugF1,
	DebugF2,
	DebugF3,
	DebugF4,
	DebugF6,
	DebugF7,
	DebugF8,
	DebugF9,


	COUNT
};


class KeyMgr
{
	friend class RCG_GameCore;

public:
	KeyMgr(const KeyMgr& _Other) = delete;
	KeyMgr(KeyMgr&& _Other) noexcept = delete;
	KeyMgr& operator=(const KeyMgr& _Other) = delete;
	KeyMgr& operator=(const KeyMgr&& _Other) noexcept = delete;


	static std::string_view EnumToString(KeyNames _Name)
	{
		return IndexToString[static_cast<size_t>(_Name)];
	}

	static bool IsPress(KeyNames _Name);
	static bool IsDown(KeyNames _Name);
	static bool IsUp(KeyNames _Name);
	static bool IsFree(KeyNames _Name);

protected:

private:
	static const std::vector<std::string_view> IndexToString;

	static void CreateKey();

	KeyMgr();
	virtual ~KeyMgr() = 0;
};

