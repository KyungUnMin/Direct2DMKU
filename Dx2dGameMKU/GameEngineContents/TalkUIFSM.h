#pragma once
#include "FSMBase.h"

enum class TalkUIState
{
	Wait,
	FadeIn,
	PlayerTalk,
	NpcTalk,
	FadeOut,

	COUNT
};

enum class TalkType
{
	Godai1,
	Godai2,
	Godai3,
	Brunov,

	UNKNOWN
};

class TalkUI;

class TalkUIFSM : public FSMBase
{
public:
	TalkUIFSM();
	~TalkUIFSM() override;

	TalkUIFSM(const TalkUIFSM& _Other) = delete;
	TalkUIFSM(TalkUIFSM&& _Other) noexcept = delete;
	TalkUIFSM& operator=(const TalkUIFSM& _Other) = delete;
	TalkUIFSM& operator=(const TalkUIFSM&& _Other) noexcept = delete;

	void Init(TalkType _Type, TalkUI* _UI);

	inline TalkUI* GetUI() const
	{
		return UIPtr;
	}

protected:

private:
	TalkType Type = TalkType::UNKNOWN;
	TalkUI* UIPtr = nullptr;
};

