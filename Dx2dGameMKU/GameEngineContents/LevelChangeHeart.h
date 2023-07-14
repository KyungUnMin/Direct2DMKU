#pragma once
#include "UIBase.h"

enum class LevelNames;

class LevelChangeHeart : public UIBase
{
public:
	LevelChangeHeart();
	~LevelChangeHeart();

	LevelChangeHeart(const LevelChangeHeart& _Other) = delete;
	LevelChangeHeart(LevelChangeHeart&& _Other) noexcept = delete;
	LevelChangeHeart& operator=(const LevelChangeHeart& _Other) = delete;
	LevelChangeHeart& operator=(const LevelChangeHeart&& _Other) noexcept = delete;

	void Init(LevelNames _NextLevel);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	static const std::string_view TexName;

	float4 TextureUV = float4{0.f,0.f, 1.f, 1.f};
	size_t NextLevel = -1;

	const float WaitTime = 6.f;
	const float Duration = 3.f;
	const float MaxScaleRatio = 5.f;
	

	void LoadImageRes();
	void CreateRender();
};
