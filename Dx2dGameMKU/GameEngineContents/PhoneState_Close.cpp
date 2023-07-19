#include "PrecompileHeader.h"
#include "PhoneState_Close.h"

#include "SoundMgr.h"
#include "RCG_GameCore.h"

#include "PhoneState_Open.h"
#include "HandPhoneUI.h"

PhoneState_Close::PhoneState_Close()
{

}

PhoneState_Close::~PhoneState_Close()
{

}

void PhoneState_Close::EnterState() 
{
	PhoneStateBase::EnterState();

	SoundMgr::PlaySFX("Phone_Close.wav").SetVolume(3.f);
	SoundMgr::BgmPauseOff();

	//�ð� �ǵ�����
	GameEngineTime::GlobalTime.SetGlobalTimeScale(1.f);

	//���� �Է� ���
	RCG_GameCore::SetCurGameState(GameState::OnField);
}

void PhoneState_Close::Update(float _DeltaTime) 
{
	PhoneStateBase::Update(_DeltaTime);

	float Ratio = GetLiveTime() / Duration;
	float ClampRatio = std::clamp(Ratio, 0.f, 1.f);

	//�� �׶��� ��� ����
	HandPhoneUI* Phone = GetPhone();
	Phone->GetBackImgColor().a = (1.f - ClampRatio) * 0.5f;

	//�� ���̾ƿ� �̵�
	float4 NextOffset = float4::Lerp(PhoneState_Open::DestOffset, PhoneState_Open::StartOffset, ClampRatio);
	GameEngineTransform* PhoneTrans = GetPhone()->GetTransform();
	PhoneTrans->SetLocalPosition(NextOffset);

	if (Ratio < 1.f)
		return;

	Phone->Off();
}
