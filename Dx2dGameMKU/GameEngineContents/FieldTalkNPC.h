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

	inline void SetTalkCallBack(std::function<bool()> _TalkCallback)
	{
		TalkCallback = _TalkCallback;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<GameEngineSpriteRenderer> IconBackRender = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> IconFrontRender = nullptr;

	const float TalkWaitDuration = 1.0f;
	float TalkWaitTime = 0.f;

	std::function<bool()> TalkCallback = nullptr;

	std::shared_ptr<GameEngineSpriteRenderer> CreateIconRender();
	void Update_Collision(float _DeltaTime);

	void TalkExcute();
};

