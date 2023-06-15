#pragma once
#include <GameEngineCore/GameEngineActor.h>

class YamadaMatterFragment : public GameEngineActor
{
public:
	YamadaMatterFragment();
	~YamadaMatterFragment() override;

	YamadaMatterFragment(const YamadaMatterFragment& _Other) = delete;
	YamadaMatterFragment(YamadaMatterFragment&& _Other) noexcept = delete;
	YamadaMatterFragment& operator=(const YamadaMatterFragment& _Other) = delete;
	YamadaMatterFragment& operator=(const YamadaMatterFragment&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	static const std::string_view Frag_FileName;
	static const float RenderOffset;
	static const float Duration;
	static const float4 MaxMoveArea;
	static bool DirSwitch;

	std::shared_ptr<class GameEngineSpriteRenderer> Render = nullptr;
	float4 MoveArea = float4::Zero;
	float4 StartPos = float4::Null;

	void CreateRender();
	void SettingValue();
};

