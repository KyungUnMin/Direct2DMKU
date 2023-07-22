#include "PrecompileHeader.h"
#include "TutorialUI.h"

#include <GameEngineCore/GameEngineLevel.h>

#include "RCG_GameCore.h"
#include "RCGEnums.h"

std::list<TutorialUI::TutorialData> TutorialUI::AllCallBack;
std::set<std::string> TutorialUI::OnceTutorialDict;

std::queue<TutorialUI::TutorialData> TutorialUI::JopQueue;

TutorialUI* TutorialUI::TutorialPtr = nullptr;


void TutorialUI::BindTurorial(
	const std::string_view& _Title,
	const std::string_view& _Desc,
	std::function<bool()> _CheckFunc /*= nullptr*/)
{
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

		if (nullptr != CheckCallBack && false == CheckCallBack())
		{
			++StartIter;
			continue;
		}

		//nullptr인 경우엔 무조건 true인 펑셔널로 취급
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




void TutorialUI::BindOnceTutorial(
	const std::string_view& _Title,
	const std::string_view& _Desc,
	std::function<bool()> _CheckFunc /*= nullptr*/)
{
	std::string Title = _Title.data();
	if (true == OnceTutorialDict.contains(Title))
		return;

	OnceTutorialDict.insert(Title);
	BindTurorial(_Title, _Desc, _CheckFunc);
}