#pragma once
#include "UIBase.h"
#include "RCGEnums.h"
#include "BossVersusUIFSM.h"

class GameEngineRenderer;
class GameEngineSpriteRenderer;


class BossVersus : public UIBase
{
public:
	static BossVersus* GetPtr();

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

	BossVersus();
	~BossVersus() override;

	BossVersus(const BossVersus& _Other) = delete;
	BossVersus(BossVersus&& _Other) noexcept = delete;
	BossVersus& operator=(const BossVersus& _Other) = delete;
	BossVersus& operator=(const BossVersus&& _Other) noexcept = delete;

	void Init(BossType _Boss);

	inline std::shared_ptr<GameEngineRenderer> GetPlayerPortrait() const
	{
		return PlayerPortrait;
	}

	inline std::shared_ptr<GameEngineRenderer> GetBossPortrait() const
	{
		return BossPortrait;
	}

protected:
	void Update(float _DeltaTime) override;

private:





	static BossVersus* GPtr;


	static const std::string_view PlayerPortrait_FileName;
	static const std::string_view SchoolPortrait_FileName;
	static const std::string_view TownPortrait_FileName;
	static const std::string_view OcenePortrait_FileName;

	static const std::string_view SchoolName_FileName;
	static const std::string_view OceneName_FileName;
	static const std::string_view PlayerName_FileName;
	static const std::string_view TownName_FileName;

	static const std::string_view PortraitPipeName;
	static const std::string_view PortraitCBufferName;

	//static const std::string_view NameTag_FileName;
	//static const std::string_view VersusLogo_FileName;
	
	
	struct ShaderData
	{
		float NoiseFilterValue = 0.0f;
		const float NoiseImageScale = 10.f; /*±âÁ¸°ª 5.0f*/
		const float Garbage1 = 0.f;
		const float Garbage2 = 0.f;
	};

	ShaderData CBufferData;
	std::shared_ptr<GameEngineRenderer> PlayerPortrait = nullptr;
	std::shared_ptr<GameEngineRenderer> BossPortrait = nullptr;

	BossVersusUIFSM Fsm;

	void LoadImages();
	void CreatePortraits(BossType _Boss);
	void CreateNames(BossType _Boss);

	void Update_PortShader(float _DeltaTime);
};

