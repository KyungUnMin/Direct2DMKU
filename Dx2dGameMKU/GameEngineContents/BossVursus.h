#pragma once
#include "UIBase.h"

enum class BossType
{
	Misuzu,
	Yamada,
	Noise
};


class GameEngineRenderer;
class GameEngineSpriteRenderer;


class BossVursus : public UIBase
{
public:
	enum class RenderType
	{
		LeftCornerBlack,
		LeftCornerPink,
		RightCornerBlack,
		RightCornerPink,
		PlayerNameTag,
		BossNameTag,
		PlayerName,
		BossName,
		VersusLogo,
		COUNT
	};

	BossVursus();
	~BossVursus() override;

	BossVursus(const BossVursus& _Other) = delete;
	BossVursus(BossVursus&& _Other) noexcept = delete;
	BossVursus& operator=(const BossVursus& _Other) = delete;
	BossVursus& operator=(const BossVursus&& _Other) noexcept = delete;

	void Init(BossType _Boss);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	static const std::string_view SchoolName_FileName;
	static const std::string_view SchoolPortrait_FileName;
	static const std::string_view OcenePortrait_FileName;
	static const std::string_view OceneName_FileName;
	static const std::string_view PlayerName_FileName;
	static const std::string_view PlayerPortrait_FileName;

	static const std::string_view NameTag_FileName;
	static const std::string_view VersusLogo_FileName;
	static const std::string_view CornerBlack_FileName;
	static const std::string_view CornerPink_FileName;
	static const std::string_view TownName_FileName;
	static const std::string_view TownPortrait_FileName;

	static const std::string_view PortraitPipeName;
	static const std::string_view PortraitCBufferName;

	std::vector<std::shared_ptr<GameEngineSpriteRenderer>> SpriteRenders;
	std::shared_ptr<GameEngineRenderer> PlayerPortrait = nullptr;
	std::shared_ptr<GameEngineRenderer> BossPortrait = nullptr;


	void LoadImages();
	void CreateRenderers();

	//-----------------------------------FSM-------------------------

private:
	enum class State
	{
		Match,
		CallName,
		Fire,
		Ready
	};

	struct ShaderData
	{
		float NoiseFilterValue = 1.0f;
		const float NoiseImageScale = 5.f;
		const float Garbage1 = 0.f;
		const float Garbage2 = 0.f;
	};

	State CurState = State::Match;
	float Timer = 0.f;
	ShaderData CBufferData;


	void Update_FSM(float _DeltaTime);
	void Update_Match();
};

