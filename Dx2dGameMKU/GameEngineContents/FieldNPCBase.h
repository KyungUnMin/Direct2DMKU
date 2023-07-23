#pragma once
#include "FieldActorBase.h"

enum class KeyNames;

class AnimationParameter;

class FieldNPCBase : public FieldActorBase
{
public:
	static const std::string IdleAniName;
	static const std::string ReactAniName;

	FieldNPCBase();
	~FieldNPCBase() override;

	FieldNPCBase(const FieldNPCBase& _Other) = delete;
	FieldNPCBase(FieldNPCBase&& _Other) noexcept = delete;
	FieldNPCBase& operator=(const FieldNPCBase& _Other) = delete;
	FieldNPCBase& operator=(const FieldNPCBase&& _Other) noexcept = delete;

	virtual void React();

	//Idle애니메이션과 React애니메이션을 생성
	virtual void AnimationCreate(const std::string_view& _NpcFolderName);

	inline void DonLookAtReact()
	{
		IsLookPlayer = false;
	}

	inline bool IsDamaged() const
	{
		return Damaged;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	
	//렌더러 오프셋 조정
	void Update_RenderTrans();

	virtual void Update_Idle(float _DeltaTime);
	virtual void Update_React(float _DeltaTime);

private:
	enum class State
	{
		Idle,
		React
	};

	State CurState = State::Idle;
	bool Damaged = false;

	//플레이어에게 공격 받았을 때 플레이어를 바라보는지 여부
	bool IsLookPlayer = true;
};

