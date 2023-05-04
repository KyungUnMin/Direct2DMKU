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
	//<텍스처 이름, 오프셋>
	static const std::vector<std::pair<std::string_view, float4>> BGInfoes;
	static const std::string_view CollisionImageName;

	void LoadImgRes();
	void CreateBackGrounds();
	void CreateDoors();
};

