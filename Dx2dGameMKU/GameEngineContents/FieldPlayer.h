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

	bool OnDamage_Face();
	bool OnDamage_Stomach();
	bool OnDamage_Jaw();
	bool OnDamage_BlowBack();

	//�ܺο��� ������ ������ ����(�������� �� ���Ͱ� �÷��̾� �����Ҷ��� ����)
	void SetDirection(bool IsRight);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	//�����ʿ��� �� �����Ӹ��� �������� �÷��̾ �������ش�
	static FieldPlayer* GPtr;

	PlayerFSM Fsm;

	//true�϶� ������, false�� ����
	bool RenderDir = true;

	//�̹� �����ӵ��ȿ�, �ܺο��� ������ ������ �����ƴ��� ����
	bool IsFixedDirection = false;
	


	std::shared_ptr<class GameEngineCollision> AttackCollider = nullptr;

	void CheckDirection();
};

