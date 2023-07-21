#include "PrecompileHeader.h"
#include "TutorialUI.h"

#include <GameEngineCore/GameEngineLevel.h>

#include "RCG_GameCore.h"
#include "RCGEnums.h"

std::list<TutorialUI::TutorialData> TutorialUI::AllCallBack;
std::queue<TutorialUI::TutorialData> TutorialUI::JopQueue;

TutorialUI* TutorialUI::TutorialPtr = nullptr;



void TutorialUI::BindTurorial(
	const std::string_view& _Title,
	const std::string_view& _Desc,
	std::function<bool()> _CheckFunc)
{
	if (nullptr == _CheckFunc)
	{
		MsgAssert("nullptr인 콜백함수를 등록할 수는 없습니다");
		return;
	}

	TutorialData& Data = AllCallBack.emplace_back();
	Data.CheckFunc = _CheckFunc;
	Data.TutoTitle = _Title;
	Data.TutoDesc = _Desc;
}


void TutorialUI::Update_CheckCallBack(GameEngineLevel* _Level)
{
	//튜토리얼 엑터가 존재한는 동안엔 콜백 검사 및 새로운 튜토리얼 액터를 만들지 않음
	if (nullptr != TutorialPtr)
		return;

	std::list<TutorialData>::iterator StartIter = AllCallBack.begin();
	std::list<TutorialData>::iterator EndIter = AllCallBack.end();

	while (StartIter != EndIter)
	{
		const TutorialData& Data = *StartIter;
		std::function<bool()> CheckCallBack = Data.CheckFunc;
		if (nullptr == CheckCallBack)
		{
			MsgAssert("nullptr인 콜백함수를 실행할 수는 없습니다");
			return;
		}

		if (false == CheckCallBack())
		{
			++StartIter;
			continue;
		}

		JopQueue.push(Data);
		StartIter = AllCallBack.erase(StartIter);
	}

	if (true == JopQueue.empty())
		return;

	if (GameState::OnField != RCG_GameCore::GetCurGameState())
		return;

	TutorialData Data = JopQueue.front();
	JopQueue.pop();

	std::shared_ptr<TutorialUI> TutorialPtr = nullptr;
	TutorialPtr = _Level->CreateActor<TutorialUI>(UpdateOrder::UI);
	TutorialPtr->Init(Data.TutoTitle, Data.TutoDesc);
}




