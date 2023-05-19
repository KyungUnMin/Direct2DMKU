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

	bool OnDamage_Face();
	bool OnDamage_Stomach();
	bool OnDamage_Jaw();
	bool OnDamage_BlowBack();

	//외부에서 강제로 방향을 설정(아직까진 적 몬스터가 플레이어 공격할때만 사용됨)
	void SetDirection(bool IsRight);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	//레벨쪽에서 매 프레임마다 실행중인 플레이어를 설정해준다
	static FieldPlayer* GPtr;

	PlayerFSM Fsm;

	//true일때 오른쪽, false면 왼쪽
	bool RenderDir = true;

	//이번 프레임동안에, 외부에서 방향을 강제로 설정됐는지 유무
	bool IsFixedDirection = false;
	


	std::shared_ptr<class GameEngineCollision> AttackCollider = nullptr;

	void CheckDirection();
};

