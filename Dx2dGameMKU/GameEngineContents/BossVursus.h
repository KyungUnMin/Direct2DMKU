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
	static const std::string_view PortraitCBufferName;

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

	inline std::shared_ptr<GameEngineRenderer> GetRender(RenderType _Type) const
	{
		if (RenderType::COUNT == _Type)
		{
			MsgAssert("유효하지 않은 접근입니다");
			return nullptr;
		}

		size_t Index = static_cast<size_t>(_Type);
		if (nullptr == SpriteRenders[Index])
		{
			MsgAssert("해당 렌더러를 만들어 준 적이 없습니다");
			return nullptr;
		}

	
	}

	inline std::shared_ptr<GameEngineRenderer> GetPlayerPortrait() const
	{
		return PlayerPortrait;
	}

	inline std::shared_ptr<GameEngineRenderer> GetBossPortrait() const
	{
		return BossPortrait;
	}

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

	std::vector<std::shared_ptr<GameEngineSpriteRenderer>> SpriteRenders;
	std::shared_ptr<GameEngineRenderer> PlayerPortrait = nullptr;
	std::shared_ptr<GameEngineRenderer> BossPortrait = nullptr;



	void LoadImages();
	void CreateRenderers();
};

