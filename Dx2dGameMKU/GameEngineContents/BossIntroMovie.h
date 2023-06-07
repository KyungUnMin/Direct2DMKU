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

	void Init(MovieType _MovieType, std::function<void()> _EndCallback = nullptr);

protected:
	void Update(float _DelatTime) override;

private:
	static const std::vector<std::string_view> MovieNames;

	std::shared_ptr<class SelfRenderer> Render = nullptr;
	std::vector<std::string> TexNames;
	std::function<void()> EndCallback = nullptr;

	void LoadSprite(const std::string_view& _MovieName);
	void CreateAnimation(const std::string_view& _MovieName);


	void DeleteThis();
};

