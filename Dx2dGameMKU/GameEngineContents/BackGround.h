#pragma once
#include <GameEngineCore/GameEngineActor.h>

class TileInfoData
{
public:
	TileInfoData()
	{

	}

	TileInfoData(int _XCount, int _YCount, float _Thickness = 0.1f)
		:XCount(_XCount)
		, YCount(_YCount)
		, Thickness(_Thickness)
	{
		
	}

	void operator=(const TileInfoData& _Other)
	{
		XCount = _Other.XCount;
		YCount = _Other.YCount;
		Thickness = _Other.Thickness;
	}

private:
	const float4 Color = float4{ 0.f, 0.f, 0.f, 0.5f };
	int XCount = 25;
	int YCount = 10;
	float Thickness = 0.1f;
};

class BackGround : public GameEngineActor
{
public:
	friend class FieldLevelBase;

	BackGround();
	~BackGround() override;

	BackGround(const BackGround& _Other) = delete;
	BackGround(BackGround&& _Other) noexcept = delete;
	BackGround& operator=(const BackGround& _Other) = delete;
	BackGround& operator=(const BackGround&& _Other) noexcept = delete;

	void CreateBackImage(const std::string_view& _ResName, const float4& _Scale, const float4& _Offset = float4::Zero);
	void CreateCollisionImage(const std::string_view& _ResName);

	bool IsBlockPos(const float4& _Pos);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	TileInfoData TileInfo;
	float4 MapScale = float4::Zero;
	std::shared_ptr <class GameEngineSpriteRenderer> ColRender = nullptr;
	std::shared_ptr <class GameEngineTexture> ColTexture = nullptr;


	void InitLevelArea(const float4& _Scale, const TileInfoData& _TileData);
	std::shared_ptr <class GameEngineRenderer> TileRender;
};

