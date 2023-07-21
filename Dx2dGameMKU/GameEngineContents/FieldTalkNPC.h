#pragma once
#include "FieldNPCBase.h"

class GameEngineSpriteRenderer;

class FieldTalkNPC : public FieldNPCBase
{
public:
	FieldTalkNPC();
	~FieldTalkNPC() override;

	FieldTalkNPC(const FieldTalkNPC& _Other) = delete;
	FieldTalkNPC(FieldTalkNPC&& _Other) noexcept = delete;
	FieldTalkNPC& operator=(const FieldTalkNPC& _Other) = delete;
	FieldTalkNPC& operator=(const FieldTalkNPC&& _Other) noexcept = delete;

	void React() final{}

	void AnimationCreate(const std::string_view& _NpcFolderName) override;

	

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<GameEngineSpriteRenderer> IconBackRender = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> IconFrontRender = nullptr;

	const float TalkWaitDuration = 1.0f;
	float TalkWaitTime = 0.f;
	bool IsTalking = false;	//∆„º≈≥Œ∑Œ ¥Î√º

	std::shared_ptr<GameEngineSpriteRenderer> CreateIconRender();
	void Update_Collision(float _DeltaTime);


};

