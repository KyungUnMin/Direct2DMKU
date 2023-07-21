#include "PrecompileHeader.h"
#include "TalkUIFSM.h"

#include "TalkUIState_Wait.h"
#include "TalkUIState_FadeIn.h"
#include "TalkUIState_PlayerTalk.h"
#include "TalkUIState_NpcTalk.h"
#include "TalkUIState_FadeOut.h"

TalkUIFSM::TalkUIFSM()
{

}

TalkUIFSM::~TalkUIFSM()
{

}


void TalkUIFSM::Init(TalkType _Type, TalkUI* _UI)
{
	Type = _Type;
	UIPtr = _UI;
	if (TalkType::UNKNOWN == Type)
	{
		MsgAssert("대화 타입을 TalkType::UNKNOWN으로 설정할 수는 없습니다");
		return;
	}

	FSMBase::ResizeStates(TalkUIState::COUNT);
	
	FSMBase::CreateState<TalkUIState_Wait>(TalkUIState::Wait);
	FSMBase::CreateState<TalkUIState_FadeIn>(TalkUIState::FadeIn);
	FSMBase::CreateState<TalkUIState_PlayerTalk>(TalkUIState::PlayerTalk);
	FSMBase::CreateState<TalkUIState_NpcTalk>(TalkUIState::NpcTalk);
	FSMBase::CreateState<TalkUIState_FadeOut>(TalkUIState::FadeOut);

	FSMBase::ChangeState(TalkUIState::Wait);
}