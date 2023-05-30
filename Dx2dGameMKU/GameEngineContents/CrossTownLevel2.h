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
	//<�ؽ�ó �̸�, ������>
	static const std::vector<std::pair<std::string_view, float4>> BGInfoes;
	static const std::string_view CollisionImageName;

	void LoadImgRes();
	void CreateBackGrounds();
	void CreateDoors();
	void CreateEnemies();
};


