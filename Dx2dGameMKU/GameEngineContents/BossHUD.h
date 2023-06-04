#pragma once
#include "UIBase.h"

class BossHUD : public UIBase
{
public:
	BossHUD();
	~BossHUD() override;

	BossHUD(const BossHUD& _Other) = delete;
	BossHUD(BossHUD&& _Other) noexcept = delete;
	BossHUD& operator=(const BossHUD& _Other) = delete;
	BossHUD& operator=(const BossHUD&& _Other) noexcept = delete;

	inline void Init(int _MaxHp)
	{
		MaxHp = static_cast<float>(_MaxHp);
		SetHp(_MaxHp);
	}

	void SetHp(int _CurHp);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	static const std::vector<std::string_view> FileNames;
	static const std::string_view KoFileName;
	static const float SlowTimeRatio;
	static const float SlowComeBackTime;
	static const float KoRenderOffTime;

	//-------------Hp-----------

	const float Duration = 1.5f;

	float4 HpRatio = float4::Zero;
	float StartRatio = 0.f;
	float DestRatio = 0.f;

	float MaxHp = -1.f;
	float Timer = 0.f;

	//-------------Hp-----------



	//-------------KO-----------
	
	std::shared_ptr<class GameEngineUIRenderer> KoRender = nullptr;
	const float TimeSlowDuration = 0.5f;
	bool IsKo = false;

	//-------------KO-----------

	void ImageLoad();
	void CreateRenders();
	
	void KoExcute();
};

//898 120 ResScale
