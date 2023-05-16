#pragma once
#include "UIBase.h"
#include "RCGEnums.h"
#include "BossVersusUIFSM.h"

class GameEngineRenderer;
class GameEngineSpriteRenderer;


/*
	UI 구조 바뀐다고 하니
	UI기능이 업데이트되면 그때 나머지 만들자
*/

class BossVersus : public UIBase
{
public:
	static BossVersus* GetPtr();

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

	static const std::string_view PlayerName_FileName;
	static const std::string_view SchoolName_FileName;
	static const std::string_view OceneName_FileName;
	static const std::string_view TownName_FileName;

	static const std::string_view PortraitPipeName;
	static const std::string_view PortraitCBufferName;

	//static const std::string_view NameTag_FileName;
	//static const std::string_view VersusLogo_FileName;
	
	struct ShaderData
	{
		const float4 FireColor = float4{ 0.f, 0.f, 1.f, 1.f };

		float NoiseFilterValue = 0.0f;
		const float NoiseImageScale = 15.f; /*기존값 5.0f*/
		const float OffsetRatio = 0.01f;
		const float Garbage2 = 0.f;
	};

	ShaderData CBufferData;
	std::shared_ptr<GameEngineRenderer> PlayerPortrait = nullptr;
	std::shared_ptr<GameEngineRenderer> BossPortrait = nullptr;

	BossVersusUIFSM Fsm;

	void LoadImages();
	void CreatePortraits(BossType _Boss);
	void CreateNameRenders(BossType _Boss);

	void Update_PortShader(float _DeltaTime);
};

