#include "PrecompileHeader.h"
#include "PhoneState_Open.h"

#include <GameEngineCore/GameEngineUIRenderer.h>

#include "RCG_GameCore.h"
#include "SoundMgr.h"

#include "PhoneFSM.h"
#include "HandPhoneUI.h"

const float4 PhoneState_Open::StartOffset = float4{ -300.f, -800.f };
const float4 PhoneState_Open::DestOffset = float4{ -300.f, 0.f };

PhoneState_Open::PhoneState_Open()
{

}

PhoneState_Open::~PhoneState_Open()
{

}



void PhoneState_Open::EnterState()
{
	PhoneStateBase::EnterState();

	SoundMgr::PlaySFX("Phone_Open.wav").SetVolume(3.f);
	SoundMgr::BgmPauseOn();

	SoundMgr::PauseAllSfx();
}

void PhoneState_Open::Update(float _DeltaTime)
{
	PhoneStateBase::Update(_DeltaTime);

	float Ratio = GetLiveTime() / Duration;
	float ClampRatio = std::clamp(Ratio, 0.f, 1.f);

	//�� �׶��� ��� ����
	HandPhoneUI* Phone = GetPhone();
	Phone->GetBackImgColor().a = ClampRatio * 0.5f;

	//�� ���̾ƿ� �̵�
	float4 NextOffset = float4::Lerp(StartOffset, DestOffset, ClampRatio);
	GameEngineTransform* PhoneTrans = GetPhone()->GetTransform();
	PhoneTrans->SetLocalPosition(NextOffset);

	if (Ratio < 1.f)
		return;

	//����â, ��ųâ, �κ��丮 �߿� ���������� ����ߴ� State�� ��ȯ
	PhoneFSM* Fsm = GetPhoneFSM();
	Fsm->ChangeState(Fsm->GetLastUserState());
}



void PhoneState_Open::ExitState()
{
	PhoneStateBase::ExitState();

	//�ð� ����
	GameEngineTime::GlobalTime.SetGlobalTimeScale(0.f);

	//�ٸ� ��ü���� ���� �Է� ����
	RCG_GameCore::SetCurGameState(GameState::HandPhoneUI);
}
