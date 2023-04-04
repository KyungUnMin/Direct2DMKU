#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GameEngineRenderer;

class TestActor : public GameEngineActor
{
public:
	TestActor();
	~TestActor();

	TestActor(const TestActor& _Other) = delete;
	TestActor(TestActor&& _Other) noexcept = delete;
	TestActor& operator=(const TestActor& _Other) = delete;
	TestActor& operator=(const TestActor&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	std::shared_ptr<GameEngineRenderer> Render0 = nullptr;
	std::shared_ptr<GameEngineRenderer> Render1 = nullptr;
	std::shared_ptr<GameEngineRenderer> Render2 = nullptr;
};

