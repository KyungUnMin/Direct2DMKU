#include "PrecompileHeader.h"
#include "HandPhoneUI.h"

#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineUIRenderer.h>
#include "ShaderUIRenderer.h"

#include "RCGDefine.h"
#include "RCGEnums.h"

HandPhoneUI::HandPhoneUI()
{

}

HandPhoneUI::~HandPhoneUI()
{

}

void HandPhoneUI::Start()
{
	UIBase::Start();
	LoadImgResAll();
	CreateRenders();

	Fsm.Init(this);
	Off();
}

void HandPhoneUI::LoadImgResAll()
{
	static bool IsLoad = false;
	if (true == IsLoad)
		return;

	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("UI");
	Dir.Move("HandPhone");
	std::vector<GameEngineFile> Files = Dir.GetAllFile({".png"});
	for (const GameEngineFile& File : Files)
	{
		GameEngineTexture::Load(File.GetFullPath());
	}

	IsLoad = true;
}

void HandPhoneUI::CreateRenders()
{
	BackImg = CreateComponent<ShaderUIRenderer>(FieldUIRenderOrder::Phone);
	BackImg->SetPipeLine(RCGDefine::GetPipeName(PipeType::DirectColor));
	BackImg->GetShaderResHelper().SetConstantBufferLink("LinkColor", BackImgColor);

	GameEngineTransform* BackTrans = BackImg->GetTransform();
	BackTrans->SetWorldScale(GameEngineWindow::GetScreenSize());
	BackTrans->SetWorldPosition(float4::Zero);

	PhoneLayout = CreateComponent<GameEngineUIRenderer>(FieldUIRenderOrder::Phone);
}



void HandPhoneUI::Open()
{
	On();
	Fsm.ChangeState(PhoneStateType::Open);
}


void HandPhoneUI::Update(float _DeltaTime)
{
	UIBase::Update(_DeltaTime);

	Fsm.Update(_DeltaTime);
}

void HandPhoneUI::ChangePhoneTexture(const std::string_view& _TexName)
{
	PhoneLayout->SetScaleToTexture(_TexName);
}
