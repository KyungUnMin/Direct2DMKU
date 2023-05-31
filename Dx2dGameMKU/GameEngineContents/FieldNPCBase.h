#pragma once
#include "FieldActorBase.h"

enum class KeyNames;

class AnimationParameter;

class FieldNPCBase : public FieldActorBase
{
public:
	static const std::string_view IdleAniName;
	static const std::string_view ReactAniName;

	FieldNPCBase();
	virtual~FieldNPCBase() = 0;

	FieldNPCBase(const FieldNPCBase& _Other) = delete;
	FieldNPCBase(FieldNPCBase&& _Other) noexcept = delete;
	FieldNPCBase& operator=(const FieldNPCBase& _Other) = delete;
	FieldNPCBase& operator=(const FieldNPCBase&& _Other) noexcept = delete;

	virtual void React();

	//렌더러 오프셋 조정
	void Update_RenderOffset();

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	
	virtual void Update_Idle(float _DeltaTime);
	virtual void Update_React(float _DeltaTime);

	void AnimationCreate(const std::string_view& _NpcFolderName);

private:
	enum class State
	{
		Idle,
		React
	};

	State CurState = State::Idle;
};

