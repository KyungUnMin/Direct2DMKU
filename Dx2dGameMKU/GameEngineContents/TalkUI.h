#pragma once
#include "UIBase.h"
#include "TalkUIFSM.h"

class GameEngineUIRenderer;
class UIFontRenderer;
class GameEngineCollision;

struct TextUI_ScripteInfo
{
	std::string_view TexName = "";
	std::string_view TextValue = "";
	std::string_view TalkerName = "";
	bool IsPlayerTalk = true;
};

class TalkUI : public UIBase
{
public:
	TalkUI();
	~TalkUI() override;

	TalkUI(const TalkUI& _Other) = delete;
	TalkUI(TalkUI&& _Other) noexcept = delete;
	TalkUI& operator=(const TalkUI& _Other) = delete;
	TalkUI& operator=(const TalkUI&& _Other) noexcept = delete;

	void Init(TalkType _Type, const float4& _ColOffset, const float4& _ColScale = float4{ 100.f, 2000.f });

	inline std::shared_ptr<GameEngineUIRenderer> GetBackRender() const
	{
		return BackRender;
	}

	inline void SetBackImgColor(const float4& _Color)
	{
		BackImgColor = _Color;
	}

	inline std::shared_ptr<UIFontRenderer> GetTextRender() const
	{
		return TextRender;
	}

	inline std::shared_ptr<UIFontRenderer> GetTalkerNameRender() const
	{
		return TalkerNameRender;
	}

	const TextUI_ScripteInfo& PickScript() const;

	const TextUI_ScripteInfo& PopScript();

	inline bool IsScriptEmpty() const
	{
		return (TalkScript.size() <= ScriptCursor);
	}

	inline std::shared_ptr<GameEngineCollision> GetCollider()  const
	{
		return Collider;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	static const std::vector<std::vector<TextUI_ScripteInfo>> AllTalkScript;

	TalkUIFSM Fsm;
	std::vector<TextUI_ScripteInfo> TalkScript;
	size_t ScriptCursor = 0;

	std::shared_ptr<GameEngineUIRenderer> BackRender = nullptr;
	std::shared_ptr<UIFontRenderer> TalkerNameRender = nullptr;
	std::shared_ptr<UIFontRenderer> TextRender = nullptr;
	std::shared_ptr<GameEngineCollision> Collider = nullptr;
	float4 BackImgColor = float4::Null;

	void ImageLoad();
	void CreateRenders();
};

