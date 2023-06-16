#include "PrecompileHeader.h"
#include "FieldEnemy_Yamada.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "RCG_GameCore.h"
#include "RCGDefine.h"
#include "RCGEnums.h"

const int FieldEnemy_Yamada::MaxHp = 240;

FieldEnemy_Yamada::FieldEnemy_Yamada()
{

}

FieldEnemy_Yamada::~FieldEnemy_Yamada()
{

}



void FieldEnemy_Yamada::Start()
{
	FieldBossBase::Start();

	Fsm.Init(this);
	SetStartHp(MaxHp);
	CreateRageRender();
}

void FieldEnemy_Yamada::SetStartHp(int _Hp)
{
	FieldBossBase::SetStartHp(_Hp);
	Fsm.SetMaxHp(_Hp);
}


void FieldEnemy_Yamada::CreateRageRender()
{
	const float OutlineRatio = 20.f;
	
	OutLineRender = CreateComponent<GameEngineSpriteRenderer>(FieldRenderOrder::ZOrder);
	OutLineRender->GetShaderResHelper().SetConstantBufferLink("AtlasData", OutLineAtlas);
	OutLineRender->ColorOptionValue.MulColor = float4::Null;

	float4 EnemyRenderScale = GetRenderer()->GetTransform()->GetLocalScale();
	GameEngineTransform* OutLineTrans = OutLineRender->GetTransform();
	OutLineTrans->SetLocalScale(EnemyRenderScale + (float4::One * OutlineRatio));
	OutLineTrans->AddLocalPosition(float4::Forward);

	OutLineRender->Off();
}





void FieldEnemy_Yamada::Update(float _DeltaTime)
{
	if (GameState::OnField != RCG_GameCore::GetCurGameState())
		return;

	FieldBossBase::Update(_DeltaTime);

	Fsm.Update(_DeltaTime);

	RageRender(_DeltaTime);
}


void FieldEnemy_Yamada::RageRender(float _DeltaTime)
{
	if (false == OutLineRender->IsUpdate())
		return;

	if (true == IsKO())
	{
		OutLineRender->Off();
		return;
	}

	//EnemyRender�� ���� �޾ƿ���
	std::shared_ptr<GameEngineSpriteRenderer> EnemyRender = GetRenderer();
	OutLineRender->SetTexture(EnemyRender->GetTexName());
	OutLineAtlas = EnemyRender->GetAtlasData();


	float LiveTime = GetLiveTime();
	float SinValue = abs(sinf(GameEngineMath::PIE * LiveTime));

	//�Ķ� ~ ����
	float4 NowColor = float4::LerpClamp(float4::Red, float4::Blue, SinValue);
	OutLineRender->ColorOptionValue.MulColor = NowColor;
}





void FieldEnemy_Yamada::Render(float _DeltaTime)
{
	if (GameState::OnField != RCG_GameCore::GetCurGameState())
		return;

	FieldBossBase::Render(_DeltaTime);

	Fsm.Render(_DeltaTime);
}



void FieldEnemy_Yamada::OnDamage(int _Damege)
{
	FieldBossBase::OnDamage(_Damege);

	size_t PrevPhase = Fsm.GetCurPhase();
	Fsm.CalPhase(GetHp());
	size_t NowPhase = Fsm.GetCurPhase();

	if (PrevPhase == NowPhase)
		return;

	//3�������� ���
	if (2 != NowPhase)
		return;

	//������ ������ ����
	OutLineRender->On();

	//������ ���� State
	//������ ��������ʹ� �ش� ����� ����������
	//�������� ���� State���� ó���� ������� ����, (������ ��길 ó����)
	//�׷��� �� ��쿡�� ���⼭ ������Ʈ �����ص� �ȴ�(���� ����� �ƴҵ�)
	Fsm.ChangeState(YamadaStateType::PhaseTransition);
}




bool FieldEnemy_Yamada::OnDamage_Face(int _Damage)
{
	OnDamage(_Damage);
	ExceptionType Result = OnDamageException();

	if (ExceptionType::DamageOk_StateChanged == Result)
		return true;

	if (ExceptionType::DamageOk_StateKeep == Result)
		return true;

	if (ExceptionType::DamageNo == Result)
		return false;

	Fsm.ChangeState(YamadaStateType::NormalDamaged_Face);
	return true;
}

bool FieldEnemy_Yamada::OnDamage_Stomach(int _Damage)
{
	OnDamage(_Damage);
	ExceptionType Result = OnDamageException();

	if (ExceptionType::DamageOk_StateChanged == Result)
		return true;

	if (ExceptionType::DamageOk_StateKeep == Result)
		return true;

	if (ExceptionType::DamageNo == Result)
		return false;

	Fsm.ChangeState(YamadaStateType::NormalDamaged_Stomach);
	return true;
}

bool FieldEnemy_Yamada::OnDamage_Jaw(int _Damage)
{
	OnDamage(_Damage);
	ExceptionType Result = OnDamageException();

	if (ExceptionType::DamageOk_StateChanged == Result)
		return true;

	if (ExceptionType::DamageOk_StateKeep == Result)
		return true;

	if (ExceptionType::DamageNo == Result)
		return false;

	Fsm.ChangeState(YamadaStateType::NormalDamaged_Jaw);
	return true;
}

bool FieldEnemy_Yamada::OnDamage_BlowBack(int _Damage)
{
	OnDamage(_Damage);
	ExceptionType Result = OnDamageException();

	if (ExceptionType::DamageOk_StateChanged == Result)
		return true;

	if (ExceptionType::DamageOk_StateKeep == Result)
		return true;

	if (ExceptionType::DamageNo == Result)
		return false;
	

	Fsm.ChangeState(YamadaStateType::Damaged_BlowBack);
	return true;
}



FieldEnemy_Yamada::ExceptionType FieldEnemy_Yamada::OnDamageException()
{
	YamadaStateType CurState = Fsm.GetNowState<YamadaStateType>();

	//������ ó���� KO�� ���
	if (true == IsKO())
	{
		//�̹� Ko�� ���
		if (YamadaStateType::Damaged_KnockDown == CurState)
			return ExceptionType::DamageNo;

		//KnockDown���·� ����
		Fsm.ChangeState(YamadaStateType::Damaged_KnockDown);
		return ExceptionType::DamageOk_StateChanged;
	}

	//���� ������ ���
	else if (YamadaStateType::Damaged_Dizzy == CurState)
	{
		Fsm.ChangeState(YamadaStateType::Damaged_GroundHit);
		return ExceptionType::DamageOk_StateChanged;
	}

	//���� ���°� ���۾Ƹ� ������ ��� FSM�� ��ȭ��Ű�� �ʰ� �������� ó��
	else if (true == Fsm.IsUnbeatableState())
		return ExceptionType::DamageOk_StateKeep;

	//������ �������� ��� FSM�� ��ȭ��Ű�� �ʰ� �������� ó��
	else if (true == Fsm.IsLastPhase())
		return ExceptionType::DamageOk_StateKeep;


	return ExceptionType::NoException;
}




void FieldEnemy_Yamada::LevelChangeEnd()
{
	FieldEnemyBase::LevelChangeEnd();

	if (YamadaStateType::Damaged_KnockDown == Fsm.GetNowState<YamadaStateType>())
		return;

	Fsm.ChangeState(YamadaStateType::Idle);
}

