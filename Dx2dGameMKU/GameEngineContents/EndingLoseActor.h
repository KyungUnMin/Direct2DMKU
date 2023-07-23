#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GameEngineSpriteRenderer;
class UIFontRenderer;

class EndingLoseActor : public GameEngineActor
{
public:
	EndingLoseActor();
	~EndingLoseActor() override;

	EndingLoseActor(const EndingLoseActor& _Other) = delete;
	EndingLoseActor(EndingLoseActor&& _Other) noexcept = delete;
	EndingLoseActor& operator=(const EndingLoseActor& _Other) = delete;
	EndingLoseActor& operator=(const EndingLoseActor&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	static const float4 TextPos;

	std::shared_ptr<GameEngineSpriteRenderer> Player = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> Light = nullptr;
	std::shared_ptr<UIFontRenderer> Text = nullptr;


	enum class State
	{
		EnterWait,
		MovePlayer,
		MoveText,
		ExitWait,
	};

	State CurState = State::EnterWait;

	void LoadImgRes();
	void CreateRenders();

	void Update_EnterWait(float _DeltaTime);
	void Update_MovePlayer(float _DeltaTime);
	void Update_MoveText(float _DeltaTime);
	void Update_ExitWait(float _DeltaTime);

	void SetGuiTarget(class GameEngineTransform* _Target);
};

