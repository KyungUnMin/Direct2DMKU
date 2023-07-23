#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GameEngineSpriteRenderer;
class GameEngineFontRenderer;

class EndingWinActor : public GameEngineActor
{
public:
	EndingWinActor();
	~EndingWinActor() override;

	EndingWinActor(const EndingWinActor& _Other) = delete;
	EndingWinActor(EndingWinActor&& _Other) noexcept = delete;
	EndingWinActor& operator=(const EndingWinActor& _Other) = delete;
	EndingWinActor& operator=(const EndingWinActor&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	static const std::string_view Background_FileName;
	static const std::string_view KyokoTexNames[2];
	static const std::string_view MisakoTexNames[2];
	static const std::string_view What_FileName;

	std::shared_ptr<GameEngineSpriteRenderer> BackGround = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> Kyoko = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> Misako = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> WhatSpeech = nullptr;
	std::shared_ptr<GameEngineFontRenderer> ThankMsg = nullptr;

	std::shared_ptr<GameEngineSpriteRenderer> RingEffect = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> SleepEffect = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> AwakeEffect = nullptr;

	enum class State
	{
		MsgFadeIn,
		MsgFadeOut,
		Ring,
		Scream,
		GameEnd,
	};

	State CurState = State::MsgFadeIn;
	float4 KyokoOriginPos = float4::Zero;
	float4 MisakoOriginPos = float4::Zero;


	void LoadImgRes();
	void CreateRenders();
	void CreateBackground();
	void CreateCharacters();
	void CreateEffects();

	std::shared_ptr<GameEngineSpriteRenderer> CreateEffect(
		const std::string_view& _TexName,
		std::shared_ptr<GameEngineSpriteRenderer> _Parent,
		const float4& _Offset,
		bool _IsGui = false);
	void CreateText();

	void Update_MsgFadeIn(float _DeltaTime);
	void Update_MsgFadeOut(float _DeltaTime);
	void Update_Ring(float _DeltaTime);
	void Update_Scream(float _DeltaTime);

	void SetGuiTarget(class GameEngineTransform* _Target);
};

