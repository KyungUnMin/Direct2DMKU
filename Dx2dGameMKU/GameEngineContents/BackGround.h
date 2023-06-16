#pragma once
#include <GameEngineCore/GameEngineActor.h>

class TileInfoData
{
	friend class BackGround;

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
	const float4 Color = float4{ 0.f, 0.f, 0.f, 1.f };
	int XCount = 25;
	int YCount = 10;
	float Thickness = 0.1f;
};



class BackGround : public GameEngineActor
{
public:
	friend class FieldLevelBase;
	friend class ShopLevelBase;

	BackGround();
	~BackGround() override;

	BackGround(const BackGround& _Other) = delete;
	BackGround(BackGround&& _Other) noexcept = delete;
	BackGround& operator=(const BackGround& _Other) = delete;
	BackGround& operator=(const BackGround&& _Other) noexcept = delete;

	//해당 위치가 픽셀충돌로 막힌 곳인지 확인
	bool IsBlockPos(const float4& _Pos) const;

	//그리드좌표에 따른 필드위치값 반환(그리드 좌표 -> 필드좌표)
	const float4& GetPosFromGrid(int _X, int _Y) const;

	//필드 좌표에 따른 그리드 좌표값 반환(필드좌표 -> 그리드 좌표)
	const std::pair<int, int> GetGridFromPos(const float4& _Pos) const;


	//해당 그리드 좌표가 막힌 곳인지 확인
	inline bool IsBlockGrid(int _X, int _Y) const
	{
		return IsBlockPos(GetPosFromGrid(_X, _Y));
	}

	inline const float4& GetGridScale() const
	{
		return GridScale;
	}

	inline std::pair<int, int> GetGridMapScale() const
	{
		return std::make_pair(TileInfo.XCount, TileInfo.YCount);
	}

	inline const float4& GetMapScale() const
	{
		return MapScale;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	TileInfoData TileInfo;
	float4 MapScale = float4::Zero;
	float4 GridScale = float4::Zero;

	float DeepMostZ = 0.f;
	std::shared_ptr <class GameEngineSpriteRenderer> ColRender = nullptr;
	std::shared_ptr <class GameEngineTexture> ColTexture = nullptr;
	std::shared_ptr <class GameEngineRenderer> TileRender;

	void InitLevelArea(const float4& _Scale, const TileInfoData& _TileData);
	std::shared_ptr<GameEngineSpriteRenderer> CreateBackImage(const std::string_view& _ResName, const float4& _Scale, const float4& _Offset = float4::Zero);
	void CreateCollisionImage(const std::string_view& _ResName);
};

