#include "PrecompileHeader.h"
#include "BossVersusState_Wait.h"

#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineRenderTarget.h>

#include "RCGEnums.h"

#include "BossVersus.h"
#include "FieldLevelBase.h"
#include "BossVersus_PostProcessing.h"

BossVersusState_Wait::BossVersusState_Wait()
{

}

BossVersusState_Wait::~BossVersusState_Wait()
{

}

void BossVersusState_Wait::Start()
{
	StateBase::Start();

	std::shared_ptr<FieldLevelBase> Level = FieldLevelBase::GetPtr();
	std::shared_ptr<GameEngineCamera> VersusCam = nullptr;

	VersusCam = Level->GetCamera(static_cast<int>(RCG_CamNumType::BossVersusUI));
	if (nullptr == VersusCam)
	{
		MsgAssert("BossVersusUIī�޶� ����� �� ���� ���µ� �� ī�޶� ����Ʈ ���μ����� ����Ϸ��� �߽��ϴ�");
		return;
	}

	std::shared_ptr<GameEngineRenderTarget> VersusCamTarget = VersusCam->GetCamTarget();
	if (nullptr == VersusCamTarget)
	{
		MsgAssert("BossVersusī�޶� ����Ÿ���� �������� �ʽ��ϴ�");
		return;
	}

	PostEffect = VersusCamTarget->CreateEffect<BossVersus_PostProcessing>();
}


void BossVersusState_Wait::EnterState()
{
	StateBase::EnterState();

	PostEffect->On(3.f, [this]()
	{
		BossVersus* VersusUI = BossVersus::GetPtr();
		if (nullptr == VersusUI)
		{
			MsgAssert("BossVersus �� �̹� �����Ǿ����ϴ�");
			return;
		}

		//TODO
		VersusUI->Off();
		VersusUI->Death();
		this->PostEffect = nullptr;
	});
}

//void BossVersusState_Wait::Update(float _DeltaTime)
//{
//	StateBase::Update(_DeltaTime);
//
//	if (GetLiveTime() < Duration)
//		return;
//
//	BossVersus* VersusUI = BossVersus::GetPtr();
//
//	//TODO
//	VersusUI->Death();
//}
