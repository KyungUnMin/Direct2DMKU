#pragma once
#include "UIBase.h"
#include <queue>

#include "RCGEnums.h"


class UIFontRenderer;
class GameEngineLevel;

class DyingMessage : public UIBase
{
public:
	DyingMessage();
	~DyingMessage() override;

	DyingMessage(const DyingMessage& _Other) = delete;
	DyingMessage(DyingMessage&& _Other) noexcept = delete;
	DyingMessage& operator=(const DyingMessage& _Other) = delete;
	DyingMessage& operator=(const DyingMessage&& _Other) noexcept = delete;

	void SetMsg(EnemyType _Type);

	void RenderOff();
	void RenderOn();

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void LevelChangeEnd() override;

private:
	static const std::vector<std::string_view> MsgOwnerNames;
	static const std::vector<std::vector<std::string_view>> MsgScript;
	static const std::vector<float4> MsgColors;
	

	std::shared_ptr<UIFontRenderer> MsgNameRender = nullptr;
	std::shared_ptr<UIFontRenderer> MsgValueRender = nullptr;

	enum class State
	{
		Ready,
		Print,
		Wait,
	};
	State CurState = State::Ready;
	std::wstring Message;
	size_t Cursor = 0;

	void Update_Print(float _DeltaTime);
	void Update_Wait(float _DeltaTime);
};

