#pragma once
#include "UIBase.h"

/*
	보스 먼저 만들고 이 대화 시스템을 만들자
*/

class ConversationUI : public UIBase
{
public:
	ConversationUI();
	~ConversationUI() override;

	ConversationUI(const ConversationUI& _Other) = delete;
	ConversationUI(ConversationUI&& _Other) noexcept = delete;
	ConversationUI& operator=(const ConversationUI& _Other) = delete;
	ConversationUI& operator=(const ConversationUI&& _Other) noexcept = delete;

	//void Excute();

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	void ImageLoad();
	void CreateBackGroundImg();
};

