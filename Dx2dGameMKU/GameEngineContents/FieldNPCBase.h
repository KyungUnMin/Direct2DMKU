#pragma once
#include "FieldActorBase.h"

enum class KeyNames;

class AnimationParameter;

class FieldNPCBase : public FieldActorBase
{
public:
	static const std::string IdleAniName;
	static const std::string ReactAniName;
	static const float4 RenderScale;

	FieldNPCBase();
	~FieldNPCBase() override;

	FieldNPCBase(const FieldNPCBase& _Other) = delete;
	FieldNPCBase(FieldNPCBase&& _Other) noexcept = delete;
	FieldNPCBase& operator=(const FieldNPCBase& _Other) = delete;
	FieldNPCBase& operator=(const FieldNPCBase&& _Other) noexcept = delete;

	virtual void React();

	//Idle�ִϸ��̼ǰ� React�ִϸ��̼��� ����
	void AnimationCreate(const std::string_view& _NpcFolderName);

	inline void DonLookAtReact()
	{
		IsLookPlayer = false;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	
	//������ ������ ����
	void Update_RenderOffset();

	virtual void Update_Idle(float _DeltaTime);
	virtual void Update_React(float _DeltaTime);

private:
	enum class State
	{
		Idle,
		React
	};

	State CurState = State::Idle;

	//�÷��̾�� ���� �޾��� �� �÷��̾ �ٶ󺸴��� ����
	bool IsLookPlayer = true;
};

