#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GameEngineRenderer;

class OpeningActor : public GameEngineActor
{
public:
	OpeningActor();
	~OpeningActor() override;

	OpeningActor(const OpeningActor& _Other) = delete;
	OpeningActor(OpeningActor&& _Other) noexcept = delete;
	OpeningActor& operator=(const OpeningActor& _Other) = delete;
	OpeningActor& operator=(const OpeningActor&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<GameEngineRenderer> Kyoko = nullptr;
	std::shared_ptr<GameEngineRenderer> Misako = nullptr;

	std::shared_ptr<GameEngineRenderer> Text_River = nullptr;
	std::shared_ptr<GameEngineRenderer> Text_City = nullptr;
	std::shared_ptr<GameEngineRenderer> Text_Girls = nullptr;
	std::shared_ptr<GameEngineRenderer> Text_Full = nullptr;

	enum class State
	{
		Video,
		Text,
		Char,
		Ready
	};

	float4 ScreenSize = float4::Zero;
	State CurState = State::Video;
	
	float4 TextScale = float4::Zero;
	float4 KyokoEndPos = float4::Zero;
	float4 MisakoEndPos = float4::Zero;

	void Update_Video();
	void Update_Char(float _DeltaTime);
	void Update_Text(float _DeltaTime);

	std::shared_ptr<GameEngineRenderer> CreateEngineTex(const std::string_view& _ResName);
};

