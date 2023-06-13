#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GameEngineSpriteRenderer;

class YamadaBlastEffect : public GameEngineActor
{
public:
	YamadaBlastEffect();
	~YamadaBlastEffect() override;

	YamadaBlastEffect(const YamadaBlastEffect& _Other) = delete;
	YamadaBlastEffect(YamadaBlastEffect&& _Other) noexcept = delete;
	YamadaBlastEffect& operator=(const YamadaBlastEffect& _Other) = delete;
	YamadaBlastEffect& operator=(const YamadaBlastEffect&& _Other) noexcept = delete;

	void Init(float _Duration, bool _IsDirRight);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	enum RenderNames
	{
		DustBack,
		DustFront,
		EndRing,
		EnergyBall,
		EnergyRing,
		Spark,

		COUNT
	};

	struct RenderInfo
	{
		std::string_view Name = "";
		int CurX = -1;
		int CurY = -1;

		float4 Offset = float4::Zero;
		float4 Scale = float4::Zero;
	};

	static const std::vector<RenderInfo> ImageInfo;



	std::vector<std::shared_ptr<GameEngineSpriteRenderer>> Renders;
	

	float Duration = -1.f;
	float4 RotateDir = float4::Zero;
	
	enum class State
	{
		Rot,

	};

	void ImageLoad();
	void CreateRenders();
};

