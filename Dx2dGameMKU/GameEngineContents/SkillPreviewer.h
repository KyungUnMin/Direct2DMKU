#pragma once
#include "FieldPlayer.h"

class GameEngineSpriteRenderer;

class SkillPreviewer : public FieldPlayer
{
public:
	SkillPreviewer();
	~SkillPreviewer() override;

	SkillPreviewer(const SkillPreviewer& _Other) = delete;
	SkillPreviewer(SkillPreviewer&& _Other) noexcept = delete;
	SkillPreviewer& operator=(const SkillPreviewer& _Other) = delete;
	SkillPreviewer& operator=(const SkillPreviewer&& _Other) noexcept = delete;


protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void LevelChangeStart() override;

private:
	static const std::string_view BackImgSpriteName;
	static const std::vector<PlayerStateType> GymSkillSlots;

	PlayerStateType CurState = PlayerStateType::COUNT;
	size_t NowSkillIndex = 0;
	int OriginPlayerMP = 0;

	void LoadAnimation();
	void CreateBackImgRender();
	void CreateLayOutRender();

	void ChangeState(PlayerStateType _NextType);
};

