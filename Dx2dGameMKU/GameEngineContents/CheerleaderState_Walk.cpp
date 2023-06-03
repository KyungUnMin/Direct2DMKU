#include "PrecompileHeader.h"
#include "CheerleaderState_Walk.h"

#include "RCGEnums.h"

#include "CheerleaderFSM.h"

#include "FieldLevelBase.h"
#include "DashSmokeEffect.h"
#include "FieldEnemyBase.h"

const std::string_view CheerleaderState_Walk::AniName = "Walk";
const std::string_view CheerleaderState_Walk::AniFileName = "Cheerleader_Walk.png";
const std::pair<int, int> CheerleaderState_Walk::AniCutFrame = std::pair<int, int>(5, 3);
const float CheerleaderState_Walk::AniInterTime = 0.08f;

CheerleaderState_Walk::CheerleaderState_Walk()
{

}

CheerleaderState_Walk::~CheerleaderState_Walk()
{

}


void CheerleaderState_Walk::Start()
{
	EnemyState_WalkBase::Start();

	LoadAnimation();
	CreateAnimation();

	EnemyState_WalkBase::SetNextState(CheerleaderStateType::Idle);
}

void CheerleaderState_Walk::LoadAnimation()
{
	static bool IsLoad = false;
	if (true == IsLoad)
		return;

	IsLoad = true;
	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("Character");
	Dir.Move("Enemy");
	Dir.Move("Cheerleader");
	Dir.Move("Movement");
	GameEngineSprite::LoadSheet(Dir.GetPlusFileName(AniFileName).GetFullPath(), AniCutFrame.first, AniCutFrame.second);
}

void CheerleaderState_Walk::CreateAnimation()
{
	std::shared_ptr<GameEngineSpriteRenderer> Render = GetRenderer();

	Render->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = AniFileName,
		.Start = 0,
		.End = 11,
		.FrameInter = AniInterTime
	});

	std::vector<size_t> Indexs = { 1, 7 };
	for (size_t Idx : Indexs)
	{
		Render->SetAnimationStartEvent(AniName, Idx, [this]()
		{
			std::shared_ptr<DashSmokeEffect> Effect = nullptr;
			Effect = FieldLevelBase::GetPtr()->CreateActor<DashSmokeEffect>(UpdateOrder::Effect);

			FieldEnemyBase* Enemy = this->GetEnemy();
			float4 EnemyPos = Enemy->GetTransform()->GetWorldPosition();

			GameEngineTransform* EffectTrans = Effect->GetTransform();
			EffectTrans->SetLocalPosition(EnemyPos);
			EffectTrans->SetLocalScale(float4::One.half());
		});
	}
}


void CheerleaderState_Walk::EnterState()
{
	EnemyState_WalkBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
}

