#pragma once
#include "FieldLevelBase.h"

class CrossTownLevel3 : public FieldLevelBase
{
public:
	CrossTownLevel3();
	~CrossTownLevel3() override;

	CrossTownLevel3(const CrossTownLevel3& _Other) = delete;
	CrossTownLevel3(CrossTownLevel3&& _Other) noexcept = delete;
	CrossTownLevel3& operator=(const CrossTownLevel3& _Other) = delete;
	CrossTownLevel3& operator=(const CrossTownLevel3&& _Other) noexcept = delete;

protected:
	void Start() override;

private:
	static const std::string_view MapImgName;
	static const float4 MapScale;

	void LoadImgRes();
	void CreateDoors();
};

