#pragma once
#include "StateBase.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "RCGDefine.h"

class EnemyFSMBase;
class FieldEnemyBase;

class EnemyStateBase : public StateBase
{
public:
	EnemyStateBase();
	virtual ~EnemyStateBase() = 0;

	EnemyStateBase(const EnemyStateBase& _Other) = delete;
	EnemyStateBase(EnemyStateBase&& _Other) noexcept = delete;
	EnemyStateBase& operator=(const EnemyStateBase& _Other) = delete;
	EnemyStateBase& operator=(const EnemyStateBase&& _Other) noexcept = delete;

protected:
	void Start() override;



	inline EnemyFSMBase* GetEnemyFsm() const
	{
		ValidCheck(FsmPtr);
		return FsmPtr;
	}

	inline FieldEnemyBase* GetEnemy() const
	{
		ValidCheck(EnemyPtr);
		return EnemyPtr;
	}

	inline std::shared_ptr<GameEngineSpriteRenderer> GetRenderer() const
	{
		ValidCheck(Renderer.get());
		return Renderer;
	}

	void ChangeRenderDirection();

	
private:
	std::shared_ptr<GameEngineSpriteRenderer> Renderer = nullptr;
	EnemyFSMBase* FsmPtr = nullptr;
	FieldEnemyBase* EnemyPtr = nullptr;

	inline void ValidCheck(void* _Ptr) const
	{
		if (nullptr != _Ptr)
			return;

		MsgAssert("EnemyState �ڽ��ʿ��� EnemyStateBase::Start�� ȣ������־�� �մϴ�");
	}
};

