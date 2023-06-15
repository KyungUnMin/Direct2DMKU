#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GameEngineSpriteRenderer;
class GameEngineCollision;

class YamadaMatterDust : public GameEngineActor
{
public:
	YamadaMatterDust();
	~YamadaMatterDust() override;

	YamadaMatterDust(const YamadaMatterDust& _Other) = delete;
	YamadaMatterDust(YamadaMatterDust&& _Other) noexcept = delete;
	YamadaMatterDust& operator=(const YamadaMatterDust& _Other) = delete;
	YamadaMatterDust& operator=(const YamadaMatterDust&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	static const std::string_view CircleEffect_FileName;
	static const std::string_view Explo_FileName;
	static const float4 ExploScale;
	static const float4 ExploOffset;
	static const int Damage;

	std::shared_ptr<GameEngineSpriteRenderer> Explo = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> CircleEffect = nullptr;
	std::shared_ptr<GameEngineCollision> Collider = nullptr;

	class FieldCamController* CamCtrl = nullptr;
	float4 CircleEffectScale = float4::Zero;
	const float Duration = 0.2f;


	void LoadSheet();
	void CreateRenders();
	void CreateCollider();
	void CheckColWithPlayer();
	void Attack();
};

