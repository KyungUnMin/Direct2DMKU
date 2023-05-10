#pragma once
#include "UIBase.h"

class BossIntroMovie : public UIBase
{
public:
	BossIntroMovie();
	~BossIntroMovie() override;

	BossIntroMovie(const BossIntroMovie& _Other) = delete;
	BossIntroMovie(BossIntroMovie&& _Other) noexcept = delete;
	BossIntroMovie& operator=(const BossIntroMovie& _Other) = delete;
	BossIntroMovie& operator=(const BossIntroMovie&& _Other) noexcept = delete;

protected:

private:

};

