#pragma once
#include <GameEngineCore/GameEngineActor.h>

enum class MoneyType
{
	Coin,
	Bill_Blue,
	Bill_Green,
	Bill_Pupple,

	UNKNOWN,
};

class GameEngineCollision;
class GameEngineSpriteRenderer;

class FieldMoney : public GameEngineActor
{
public:
	FieldMoney();
	~FieldMoney();

	FieldMoney(const FieldMoney& _Other) = delete;
	FieldMoney(FieldMoney&& _Other) noexcept = delete;
	FieldMoney& operator=(const FieldMoney& _Other) = delete;
	FieldMoney& operator=(const FieldMoney&& _Other) noexcept = delete;

	void Init(MoneyType _Type);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	struct MoneyInfo
	{
		std::string_view SpriteName;
		int Value = 0;
		size_t EndFrm = 0;
	};

	static const std::vector<MoneyInfo> MoneyInfoes;
	static const float ShadowOffsetRange;
	static const std::vector<float> BillShadowOffsetX;
	static const float ShadowOffetY;

	MoneyType Type = MoneyType::UNKNOWN;
	std::shared_ptr<GameEngineCollision> Collider = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> Render = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> Shadow = nullptr;
	bool IsLand = false;

	void LoadImageRes();
	void CreateCollision();
	void CreateRender();
	void CreateShadow();

	void Update_Collision();
	void Update_Coin(float _DeltaTime);
	void Update_Bill(float _DeltaTime);
};

