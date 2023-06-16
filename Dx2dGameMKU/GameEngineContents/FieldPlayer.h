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

	void Look(const float4& _LookPos);

	bool IsBlowing() const;

	bool IsStuned() const;

	bool OnDamage_Face(bool _IsDefenceBreak = false, bool _IsIgnoreBlow = false);
	bool OnDamage_Stomach(bool _IsDefenceBreak = false, bool _IsIgnoreBlow = false);
	bool OnDamage_Jaw(bool _IsDefenceBreak = false, bool _IsIgnoreBlow = false);
	bool OnDamage_BlowBack(bool _IsDefenceBreak = false, bool _IsIgnoreBlow = false);
	bool OnDamage_Stun(bool _IsDefenceBreak = false, bool _IsIgnoreBlow = false);

	//�ܺο��� ������ ������ ����(true�� �������� �ٶ󺻴�)
	void SetDirection(bool IsRight);

	//�÷��̾��� �̵������� ���� ���� ��ȯ
	float4 GetMoveDirVec();

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

	void LevelChangeEnd() override;

private:
	//�����ʿ��� �� �����Ӹ��� �������� �÷��̾ �������ش�
	static FieldPlayer* GPtr;


	PlayerFSM Fsm;

	//true�϶� ������, false�� ����
	bool RenderDir = true;

	//�̹� �����ӵ��ȿ�, �ܺο��� ������ ������ �����ƴ��� ����
	bool IsFixedDirection = false;
	


	std::shared_ptr<class GameEngineCollision> AttackCollider = nullptr;

	
	const float4 DamageEffect_FaceOffset = float4{ 50.f, 150.f, -100.f };
	const float4 DamageEffect_StomachOffset = float4{ 0.f, 100.f, -100.f };
	const float4 DamageEffect_JawOffset = float4{ 0.f, 150.f, -100.f };
	const float4 DamageEffect_BlowBackOffset = float4{ 0.f, 100.f, -100.f };


	float4 PrevPos = float4::Zero;

	void CheckDirection();

	//�÷��̾ ���ݹ����� �������� �޴� ��Ȳ���� üũ
	bool CanPlayerDamage(bool _IsBreakDefence = false, bool _IsIgnoreBlow = false);

	void CreateDamageEffect(const float4& _Offset);
};

