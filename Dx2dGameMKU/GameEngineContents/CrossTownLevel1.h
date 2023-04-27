#pragma once
#include "FieldLevelBase.h"

class CrossTownLevel1 : public FieldLevelBase
{
public:
	CrossTownLevel1();
	~CrossTownLevel1() override;

	CrossTownLevel1(const CrossTownLevel1& _Other) = delete;
	CrossTownLevel1(CrossTownLevel1&& _Other) noexcept = delete;
	CrossTownLevel1& operator=(const CrossTownLevel1& _Other) = delete;
	CrossTownLevel1& operator=(const CrossTownLevel1&& _Other) noexcept = delete;

protected:
	void Start() override;

private:
	static const std::string_view MapImgName;
	static const float4 MapScale;

	void LoadImgRes();
};

