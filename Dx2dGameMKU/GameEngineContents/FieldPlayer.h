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
			MsgAssert("���� �������� �÷��̾ �������� �ʽ��ϴ�");
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


	//ī�޶󿡼� �����
	bool IsDashing() const;
	
	inline bool IsRightDir() const
	{
		return RenderDir;
	}

	//Enemy Attack�ʿ��� ȣ�����ִ� �÷��̾� ���� ���� �Լ�
	void LookFixDir(bool _IsRight);

	void Look(const float4& _LookPos) override;

	bool IsBlowing() const;

	bool IsStuned() const;

	bool OnDamage_Face(int _Damage, bool _IsDefenceBreak = false, bool _IsIgnoreBlow = false);
	bool OnDamage_Stomach(int _Damage, bool _IsDefenceBreak = false, bool _IsIgnoreBlow = false);
	bool OnDamage_Jaw(int _Damage, bool _IsDefenceBreak = false, bool _IsIgnoreBlow = false);
	bool OnDamage_BlowBack(int _Damage, bool _IsDefenceBreak = false, bool _IsIgnoreBlow = false);
	bool OnDamage_Stun(int _Damage, bool _IsDefenceBreak = false, bool _IsIgnoreBlow = false);

	//�ܺο��� ������ ������ ����(true�� �������� �ٶ󺻴�)
	void SetDirection(bool IsRight);

	//�÷��̾��� �̵������� ���� ���� ��ȯ
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
	//�����ʿ��� �� �����Ӹ��� �������� �÷��̾ �������ش�
	static FieldPlayer* GPtr;
	static const std::string_view LevelUpText_FileName;


	PlayerFSM Fsm;

	//true�϶� ������, false�� ����
	bool RenderDir = true;

	//�̹� �����ӵ��ȿ�, �ܺο��� ������ ������ �����ƴ��� ����
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

	//�÷��̾ ���ݹ����� �������� �޴� ��Ȳ���� üũ
	bool CanPlayerDamage(bool _IsBreakDefence = false, bool _IsIgnoreBlow = false);

	void CreateDamageEffect(const float4& _Offset);
};

