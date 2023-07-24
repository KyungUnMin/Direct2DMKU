#pragma once
#include "FieldActorBase.h"
#include "PlayerFSM.h"

class FieldPlayer : public FieldActorBase
{
	friend class FieldLevelBase;

public:
	static std::shared_ptr<FieldPlayer> GetPtr()
	{
		if (nullptr == GPtr)
		{
			MsgAssert("아직 실행중인 플레이어가 존재하지 않습니다");
			return nullptr;
		}
		
		return GPtr->DynamicThis<FieldPlayer>();
	}


	FieldPlayer();
	~FieldPlayer() override;

	FieldPlayer(const FieldPlayer& _Other) = delete;
	FieldPlayer(FieldPlayer&& _Other) noexcept = delete;
	FieldPlayer& operator=(const FieldPlayer& _Other) = delete;
	FieldPlayer& operator=(const FieldPlayer&& _Other) noexcept = delete;


	//카메라에서 사용중
	bool IsDashing() const;
	
	inline bool IsRightDir() const
	{
		return RenderDir;
	}

	//Enemy Attack쪽에서 호출해주는 플레이어 방향 설정 함수
	void LookFixDir(bool _IsRight);

	void Look(const float4& _LookPos) override;

	bool IsBlowing() const;

	bool IsStuned() const;

	bool OnDamage_Face(int _Damage, bool _IsDefenceBreak = false, bool _IsIgnoreBlow = false);
	bool OnDamage_Stomach(int _Damage, bool _IsDefenceBreak = false, bool _IsIgnoreBlow = false);
	bool OnDamage_Jaw(int _Damage, bool _IsDefenceBreak = false, bool _IsIgnoreBlow = false);
	bool OnDamage_BlowBack(int _Damage, bool _IsDefenceBreak = false, bool _IsIgnoreBlow = false);
	bool OnDamage_Stun(int _Damage, bool _IsDefenceBreak = false, bool _IsIgnoreBlow = false);

	//외부에서 강제로 방향을 설정(true면 오른쪽을 바라본다)
	void SetDirection(bool IsRight);

	//플레이어의 이동방향을 담은 벡터 반환
	float4 GetMoveDirVec();

	void StateChange_BattleStart();

	inline PlayerStateType GetCurState() const
	{
		return Fsm.GetNowState<PlayerStateType>();
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

	void LevelChangeEnd() override;

	inline PlayerFSM& GetFsm()
	{
		return Fsm;
	}

private:
	//레벨쪽에서 매 프레임마다 실행중인 플레이어를 설정해준다
	static FieldPlayer* GPtr;
	static const std::string_view LevelUpText_FileName;


	PlayerFSM Fsm;

	//true일때 오른쪽, false면 왼쪽
	bool RenderDir = true;

	//이번 프레임동안에, 외부에서 방향을 강제로 설정됐는지 유무
	bool IsFixedDirection = false;
	


	std::shared_ptr<class GameEngineCollision> AttackCollider = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> LevelUpText = nullptr;
	
	const float4 DamageEffect_FaceOffset = float4{ 50.f, 150.f, -100.f };
	const float4 DamageEffect_StomachOffset = float4{ 0.f, 100.f, -100.f };
	const float4 DamageEffect_JawOffset = float4{ 0.f, 150.f, -100.f };
	const float4 DamageEffect_BlowBackOffset = float4{ 0.f, 100.f, -100.f };


	float4 PrevPos = float4::Zero;

	void CreateLevelUpRender();

	void CheckDirection();

	//플레이어가 공격받을때 데미지를 받는 상황인지 체크
	bool CanPlayerDamage(bool _IsBreakDefence = false, bool _IsIgnoreBlow = false);

	void CreateDamageEffect(const float4& _Offset);
};

