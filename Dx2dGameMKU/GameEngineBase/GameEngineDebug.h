#pragma once
#include <assert.h>
#include <Windows.h>
#include <string>

namespace GameEngineDebug
{
	void LeakCheck();
	void LeakPointBreak(int _Value);
}



#define MsgAssert(MsgText) std::string ErrorText = MsgText; MessageBoxA(nullptr, ErrorText.c_str(), "Error", MB_OK); assert(false);

#define MsgTextBox(MsgText) std::string ErrorText = MsgText; MessageBoxA(nullptr, ErrorText.c_str(), "Message", MB_OK);