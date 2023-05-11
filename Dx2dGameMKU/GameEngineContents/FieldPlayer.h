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
		
		return GPtr->Shared_This_dynamic_pointer<FieldPlayer>();
	}


	FieldPlayer();
	~FieldPlayer() override;

	FieldPlayer(const FieldPlayer& _Other) = delete;
	FieldPlayer(FieldPlayer&& _Other) noexcept = delete;
	FieldPlayer& operator=(const FieldPlayer& _Other) = delete;
	FieldPlayer& operator=(const FieldPlayer&& _Other) noexcept = delete;

	
	inline bool IsDashing() const
	{
		//ī�޶󿡼� �����
		return (PlayerStateType::Dash == Fsm.GetNowState<PlayerStateType>());
	}


protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	//�����ʿ��� �� �����Ӹ��� �������� �÷��̾ �������ش�
	static FieldPlayer* GPtr;

	PlayerFSM Fsm;

};

