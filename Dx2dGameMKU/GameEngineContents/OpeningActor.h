#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEnginePlatform/GameEngineSound.h>


class GameEngineSpriteRenderer;

class OpeningActor : public GameEngineActor
{
public:
	OpeningActor();
	~OpeningActor() override;

	OpeningActor(const OpeningActor& _Other) = delete;
	OpeningActor(OpeningActor&& _Other) noexcept = delete;
	OpeningActor& operator=(const OpeningActor& _Other) = delete;
	OpeningActor& operator=(const OpeningActor&& _Other) noexcept = delete;

	//State가 Video에서 Bright로 넘어가는 순간
	void VideoOff();

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<GameEngineSpriteRenderer> Kyoko = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> Misako = nullptr;
							   
	std::shared_ptr<GameEngineSpriteRenderer> Text_River = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> Text_City = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> Text_Girls = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> Text_Full = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> BrightBack = nullptr;
	//GameEngineSound BgmPlayer;

	enum class State
	{
		Video,
		Bright,
		Text,
		Char,
		Ready
	};

	float4 ScreenSize = float4::Zero;
	State CurState = State::Video;
	
	float4 TextScale = float4::Zero;
	float4 KyokoEndPos = float4::Zero;
	float4 MisakoEndPos = float4::Zero;

	void CreateBackImage();
	void CreateCharecters();
	void CreateFrame();
	void CreateTitles();
	void CraeteBrightImages();

	void Update_Bright(float _DeltaTime);
	void Update_Char(float _DeltaTime);
	void Update_Text(float _DeltaTime);
	void Update_Ready();
};

