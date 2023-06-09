#pragma once
#include "UIBase.h"
#include "RCGEnums.h"
#include "BossVersusUIFSM.h"

class SelfRenderer;
class GameEngineSpriteRenderer;



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

	inline std::shared_ptr<SelfRenderer> GetPlayerPortrait() const
	{
		return PlayerPortrait;
	}

	inline std::shared_ptr<SelfRenderer> GetBossPortrait() const
	{
		return BossPortrait;
	}

	inline std::shared_ptr <SelfRenderer> GetPlayerName() const
	{
		return PlayerNameRender;
	}

	inline std::shared_ptr <SelfRenderer> GetBossName() const
	{
		return BossNameRender;
	}

	std::shared_ptr<SelfRenderer> CreataEngineUIRender(const std::string_view& _TexFileName, BossVersusUIRenderOrder _RenderOrder);

	inline void SetCallBack(std::function<void()> _DestroyCallBack)
	{
		DestroyCallBack = _DestroyCallBack;
	}

protected:
	void Update(float _DeltaTime) override;

	void Destroy() override;

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

	static const std::string_view PortraitCBufferName;

	struct ShaderData
	{
		const float4 FireColor = float4{ 1.f, 1.f, 1.f, 1.f };

		float NoiseFilterValue = 0.0f;
		const float NoiseImageScale = 15.f; /*������ 5.0f*/
		const float OffsetRatio = 0.02f;
		const float Garbage2 = 0.f;
	};

	ShaderData CBufferData;
	std::shared_ptr<SelfRenderer> PlayerPortrait = nullptr;
	std::shared_ptr<SelfRenderer> BossPortrait = nullptr;

	std::shared_ptr<SelfRenderer> PlayerNameRender = nullptr;
	std::shared_ptr<SelfRenderer> BossNameRender = nullptr;

	BossVersusUIFSM Fsm;
	std::function<void()> DestroyCallBack = nullptr;

	void LoadImages();
	void CreatePortraits(BossType _Boss);
	void CreateNameRenders(BossType _Boss);

	void Update_PortShader(float _DeltaTime);
};

