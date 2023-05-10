#pragma once
#include "UIBase.h"

enum class MovieType
{
	School,
	Town,
	Ocean
};

class BossIntroMovie : public UIBase
{
public:
	BossIntroMovie();
	~BossIntroMovie() override;

	BossIntroMovie(const BossIntroMovie& _Other) = delete;
	BossIntroMovie(BossIntroMovie&& _Other) noexcept = delete;
	BossIntroMovie& operator=(const BossIntroMovie& _Other) = delete;
	BossIntroMovie& operator=(const BossIntroMovie&& _Other) noexcept = delete;

	void Init(MovieType _MovieType);

protected:
	void Start() override;
	void Update(float _DelatTime) override;

private:
	static const std::vector<std::string_view> MovieNames;

	std::shared_ptr<class AnimationInfo> AniCtrl = nullptr;

	void LoadSprites();
};

