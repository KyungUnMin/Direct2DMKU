#pragma once
#include <string>
#include <string_view>



class GameEngineString
{
public:
	static std::string ToUpper(const std::string_view& _Str);
	static std::string ToString(int Value);
	
	//MBCS-> WBCS
	static std::wstring AnsiToUniCode(const std::string_view& _Text);
	//유니코드 -> MBCS
	static std::string UniCodeToAnsi(const std::wstring_view& _Text);
	//WBCS -> UTF
	static std::string UniCodeToUTF8(const std::wstring_view& _Text);
	//MBCS -> WBCS -> UTF
	static std::string AnsiToUTF8(const std::string_view& _Text);

protected:

private:
	GameEngineString();
	~GameEngineString();

	GameEngineString(const GameEngineString& _Other) = delete;
	GameEngineString(GameEngineString&& _Other) noexcept = delete;
	GameEngineString& operator=(const GameEngineString& _Other) = delete;
	GameEngineString& operator=(GameEngineString&& _Other) noexcept = delete;
};

