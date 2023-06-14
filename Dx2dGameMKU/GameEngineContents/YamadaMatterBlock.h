#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GameEngineSpriteRenderer;
class GameEngineComponent;

class YamadaMatterBlock : public GameEngineActor
{
public:
	static const float BlockOffsetX;

	YamadaMatterBlock();
	~YamadaMatterBlock() override;

	YamadaMatterBlock(const YamadaMatterBlock& _Other) = delete;
	YamadaMatterBlock(YamadaMatterBlock&& _Other) noexcept = delete;
	YamadaMatterBlock& operator=(const YamadaMatterBlock& _Other) = delete;
	YamadaMatterBlock& operator=(const YamadaMatterBlock&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	static const std::string_view BlockName;
	static const std::string_view DustName;
	static const std::string_view FragmentName;

	std::shared_ptr<GameEngineSpriteRenderer> Block = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> Dust = nullptr;
	std::shared_ptr<GameEngineComponent> Pivot = nullptr;
	

	//파편들, <포인터, 벡터>
	std::vector<std::pair<std::shared_ptr<GameEngineSpriteRenderer>, float4>> Fragments;

	void ImageLoad();
	void CreateRenders();
	void CreateLight();
};

