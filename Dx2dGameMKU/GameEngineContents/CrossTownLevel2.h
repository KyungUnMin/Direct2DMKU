#pragma once
#include "FieldLevelBase.h"

class CrossTownLevel2 : public FieldLevelBase
{
public:
	CrossTownLevel2();
	~CrossTownLevel2() override;

	CrossTownLevel2(const CrossTownLevel2& _Other) = delete;
	CrossTownLevel2(CrossTownLevel2&& _Other) noexcept = delete;
	CrossTownLevel2& operator=(const CrossTownLevel2& _Other) = delete;
	CrossTownLevel2& operator=(const CrossTownLevel2&& _Other) noexcept = delete;

protected:
	void Start() override;

private:
	static const std::string_view MapImgName;
	static const float4 MapScale;

	void LoadImgRes();
};


