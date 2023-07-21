#include "PrecompileHeader.h"
#include "TalkUI.h"

#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineUIRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "RCGEnums.h"
#include "RCGDefine.h"
#include "FontMgr.h"

#include "ShaderUIRenderer.h"
#include "UIFontRenderer.h"



TalkUI::TalkUI()
{

}

TalkUI::~TalkUI()
{

}


void TalkUI::Start()
{
	UIBase::Start();

	ImageLoad();
	CreateRenders();
	Collider = CreateComponent<GameEngineCollision>(CollisionOrder::NPCTalk);
	Collider->SetColType(ColType::AABBBOX2D);
}


void TalkUI::ImageLoad()
{
	static bool IsLoad = false;
	if (true == IsLoad)
		return;

	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("UI");
	Dir.Move("Conversation");
	std::vector<GameEngineFile> Files = Dir.GetAllFile({ ".png" });
	for (const GameEngineFile& File : Files)
	{
		GameEngineTexture::Load(File.GetFullPath());
	}

	IsLoad = true;
}



void TalkUI::Init(TalkType _Type, const float4& _ColOffset /*= float4::Zero*/, const float4& _ColScale /*= float4{ 100.f, 2000.f }*/)
{
	TalkScript = AllTalkScript[static_cast<size_t>(_Type)];
	Fsm.Init(_Type, this);

	GameEngineTransform* ColliderTrans = Collider->GetTransform();
	ColliderTrans->SetLocalScale(_ColScale);
	ColliderTrans->SetLocalPosition(_ColOffset);
}


void TalkUI::CreateRenders()
{
	//백그라운드 렌더
	{
		BackRender = CreateComponent<ShaderUIRenderer>(FieldUIRenderOrder::Conversation);
		BackRender->SetPipeLine(RCGDefine::GetPipeName(PipeType::DirectColor));
		BackRender->GetShaderResHelper().SetConstantBufferLink("LinkColor", BackImgColor);

		GameEngineTransform* BackTrans = BackRender->GetTransform();
		BackTrans->SetWorldScale(GameEngineWindow::GetScreenSize());
		BackTrans->SetWorldPosition(float4::Zero);

		BackRender->Off();
	}

	//대화 텍스트
	{
		const float4 Offset = float4{-430.f, -302.f};

		TextRender = CreateComponent<UIFontRenderer>(FieldUIRenderOrder::ConversationText);
		TextRender->SetFont(FontMgr::GetFontName(FontType::Binggrae));
		TextRender->SetScale(30);
		TextRender->SetColor(float4::White);
		TextRender->SetFontFlag(FW1_TEXT_FLAG::FW1_LEFT);

		TextRender->GetTransform()->SetLocalPosition(Offset);
		TextRender->Off();
	}

	//말하는 사람 이름
	{
		const float4 Offset = float4{ -450.f, -302.f };

		TalkerNameRender = CreateComponent<UIFontRenderer>(FieldUIRenderOrder::ConversationText);
		TalkerNameRender->SetFont(FontMgr::GetFontName(FontType::Binggrae));
		TalkerNameRender->SetScale(30);
		TalkerNameRender->SetColor(float4::White);
		TalkerNameRender->SetFontFlag(FW1_TEXT_FLAG::FW1_RIGHT);

		TalkerNameRender->GetTransform()->SetLocalPosition(Offset);
		TalkerNameRender->Off();
	}
}




void TalkUI::Update(float _DeltaTime) 
{
	UIBase::Update(_DeltaTime);

	if (true == TalkScript.empty() && TalkUIState::FadeOut != Fsm.GetNowState<TalkUIState>())
	{
		MsgAssert("Init함수를 호출하지 않았습니다");
		return;
	}

	Fsm.Update(_DeltaTime);
}



const TextUI_ScripteInfo& TalkUI::PickScript() const
{
	if (true == IsScriptEmpty())
	{
		MsgAssert("더이상 볼 수 있는 스크립트가 존재하지 않습니다");
	}

	return TalkScript[ScriptCursor];
}

const TextUI_ScripteInfo& TalkUI::PopScript()
{
	if (true == IsScriptEmpty())
	{
		MsgAssert("더이상 볼 수 있는 스크립트가 존재하지 않습니다");
	}

	return TalkScript[ScriptCursor++];
}


void TalkUI::Destroy()
{
	UIBase::Destroy();

	if (nullptr == DestroyCallBack)
		return;

	DestroyCallBack();
	DestroyCallBack = nullptr;
}


void TalkUI::Excute()
{
	Collider->Off();
	Fsm.ChangeState(TalkUIState::FadeIn);
}