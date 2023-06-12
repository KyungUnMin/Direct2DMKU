#pragma once
#include <GameEngineCore/GameEngineActor.h>

//다양한 불빛을 만들려면 enum 사용하자
enum class LightType
{
	Flicker,

};

class GameEngineSpriteRenderer;

class LightEffect : public GameEngineActor
{
public:
	LightEffect();
	~LightEffect();

	LightEffect(const LightEffect& _Other) = delete;
	LightEffect(LightEffect&& _Other) noexcept = delete;
	LightEffect& operator=(const LightEffect& _Other) = delete;
	LightEffect& operator=(const LightEffect&& _Other) noexcept = delete;

	void Flicker(float4 _LightColor, float _Duration = 0.5f);

	GameEngineTransform* GetRenderTrans();

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	static const std::string_view Light_FileName;
	static const float4 LightScale;

	std::shared_ptr<GameEngineSpriteRenderer> Light = nullptr;


	float Timer = 0.f;
	float Duration = 0.f;

	void ImageLoad();
	void CreateRenders();
	void Update_Flickering();
};

