#include "GameEngineString.h"
#include <Windows.h>
#include "GameEngineDebug.h"

GameEngineString::GameEngineString()
{
}

GameEngineString::~GameEngineString()
{
}


std::string GameEngineString::ToUpper(const std::string_view& _Str)
{
	std::string Text = _Str.data();

	for (size_t i = 0; i < Text.size(); ++i)
	{
		Text[i] = toupper(Text[i]);
	}

	return Text;
}

std::string GameEngineString::ToString(int Value)
{
	return std::to_string(Value);
}

std::wstring GameEngineString::AnsiToUniCode(const std::string_view& _Text)
{
	//변환될 문자열의 길이 알아오기
	int Size = MultiByteToWideChar(CP_ACP, 0, _Text.data(), static_cast<int>(_Text.size()), nullptr, 0);
	if (0 == Size)
	{
		MsgAssert("문자열 변환에 실패하였습니다");
		return L"";
	}

	//문자열 공간 만들기
	std::wstring Result;
	Result.resize(Size);

	//문자열 변환하기
	Size = MultiByteToWideChar(CP_ACP, 0, _Text.data(), static_cast<int>(_Text.size()), &Result[0], Size);
	if (0 == Size)
	{
		MsgAssert("문자열 변환에 실패하였습니다");
		return L"";
	}

	return Result;
}

std::string GameEngineString::UniCodeToAnsi(const std::wstring_view& _Text)
{
	//변환될 문자열의 길이 알아오기
	int Size = WideCharToMultiByte(CP_ACP, 0, _Text.data(), static_cast<int>(_Text.size()), nullptr, 0, nullptr, nullptr);
	if (0 == Size)
	{
		MsgAssert("문자열 변환에 실패하였습니다");
		return "";
	}

	//문자열 공간 만들기
	std::string Result;
	Result.resize(Size);

	//문자열 변환하기
	Size = WideCharToMultiByte(CP_ACP, 0, _Text.data(), static_cast<int>(_Text.size()), &Result[0], Size, nullptr, nullptr);
	if (0 == Size)
	{
		MsgAssert("문자열 변환에 실패하였습니다");
		return "";
	}

	return Result;
}

std::string GameEngineString::UniCodeToUTF8(const std::wstring_view& _Text)
{
	//변환될 문자열의 길이 알아오기
	int Size = WideCharToMultiByte(CP_UTF8, 0, _Text.data(), static_cast<int>(_Text.size()), nullptr, 0, nullptr, nullptr);
	if (0 == Size)
	{
		MsgAssert("문자열 변환에 실패하였습니다");
		return "";
	}

	//문자열 공간 만들기
	std::string Result;
	Result.resize(Size);

	//문자열 변환하기
	Size = WideCharToMultiByte(CP_UTF8, 0, _Text.data(), static_cast<int>(_Text.size()), &Result[0], Size, nullptr, nullptr);
	if (0 == Size)
	{
		MsgAssert("문자열 변환에 실패하였습니다");
		return "";
	}

	return Result;
}

std::string GameEngineString::AnsiToUTF8(const std::string_view& _Text)
{
	//MBCS -> WBCS
	std::wstring Unicode = AnsiToUniCode(_Text);

	//WBCS -> UTF
	return UniCodeToUTF8(Unicode.c_str());
}


