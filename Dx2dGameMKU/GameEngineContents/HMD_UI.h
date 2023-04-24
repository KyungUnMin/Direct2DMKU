#pragma once
#include <GameEngineCore/GameEngineActor.h>

class HMD_UI : public GameEngineActor
{
public:
	HMD_UI();
	~HMD_UI() override;

	HMD_UI(const HMD_UI& _Other) = delete;
	HMD_UI(HMD_UI&& _Other) noexcept = delete;
	HMD_UI& operator=(const HMD_UI& _Other) = delete;
	HMD_UI& operator=(const HMD_UI&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

