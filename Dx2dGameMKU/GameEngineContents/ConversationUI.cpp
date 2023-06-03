#include "PrecompileHeader.h"
#include "ConversationUI.h"

#include <GameEngineCore/GameEngineTexture.h>

#include "RCGDefine.h"
#include "RCGEnums.h"

#include "ShaderUIRenderer.h"

ConversationUI::ConversationUI()
{

}

ConversationUI::~ConversationUI()
{

}


void ConversationUI::Start()
{
	UIBase::Start();

	ImageLoad();

}


void ConversationUI::ImageLoad()
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

void ConversationUI::CreateBackGroundImg()
{
	std::shared_ptr<ShaderUIRenderer> Render = nullptr;
	Render = CreateComponent<ShaderUIRenderer>(FieldUIRenderOrder::Conversation_BackImg);

}


void ConversationUI::Update(float _DeltaTime)
{
	UIBase::Update(_DeltaTime);


}