#pragma once
#include <GameEngineCore/GameEngineLevel.h>

enum class LevelNames;

class ShopLevelBase : public GameEngineLevel
{
	friend class LevelMgr;

public:
	ShopLevelBase();
	virtual ~ShopLevelBase() = 0;

	ShopLevelBase(const ShopLevelBase& _Other) = delete;
	ShopLevelBase(ShopLevelBase&& _Other) noexcept = delete;
	ShopLevelBase& operator=(const ShopLevelBase& _Other) = delete;
	ShopLevelBase& operator=(const ShopLevelBase&& _Other) noexcept = delete;

	//레벨이 전환되고 있는 중인지 확인
	static bool IsLevelExiting()
	{
		return (nullptr != LevelExitFade);
	}



protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void LevelChangeStart() override;
	void LevelChangeEnd() override;

	void CreateBackImage(const std::string_view& _BackImageName);

private:
	static LevelNames PrevLevel;
	static std::string PrevLevelBgmName;
	static std::shared_ptr<class Fader> LevelExitFade;


	std::shared_ptr<class ShopItem_CursorBar> Cursor = nullptr;
	std::shared_ptr<class ShopSlotController> SlotCtrl = nullptr;
	float LevelTimer = 0.f;

	UINT ThisBgmPos = 0;
	UINT PrevLevelBgmPos = 0;
	std::shared_ptr<class ShopUI_ResultText> ResultText = nullptr;



	void ImageResLoad();
};
