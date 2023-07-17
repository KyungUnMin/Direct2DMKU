#include "PrecompileHeader.h"
#include "LevelUpUICtrl.h"

#include <GameEngineCore/GameEngineSprite.h>
#include <GameEngineCore/GameEngineUIRenderer.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineFont.h>
#include "UIFontRenderer.h"

#include "RCGDefine.h"
#include "RCGEnums.h"
#include "DataMgr.h"
#include "SkillMgr.h"

#include "FieldLevelBase.h"
#include "PlayerFSM.h"

const std::string_view LevelUpUICtrl::GrowthInfo_FileName = "LevelUpUI_GrowthInfo.png";
const std::string_view LevelUpUICtrl::NewSkillBoard_FileName = "LevelUpUI_NewSkillBoard";
const std::vector<std::string_view> LevelUpUICtrl::AcquireSkillNames =
{
	"LevelUpUI_AcquireSkill_DonkeyKick.png",
	"LevelUpUI_AcquireSkill_BackKick.png",
	"LevelUpUI_AcquireSkill_CrescentKick.png",
};

std::vector<std::pair<int, PlayerStateType>> LevelUpUICtrl::LevelUpSkills =
{
	{2, PlayerStateType::SpecialAttack_DonkeyKick},
	{3, PlayerStateType::QuickAttack_BackKick},
	{4, PlayerStateType::QuickAttack_CrescentKick},
};


const std::pair<float4, float4> LevelUpUICtrl::GrowBoxPoses =
{
	{-712.f, 100.f},{-512.f, 100.f},
};



LevelUpUICtrl::LevelUpUICtrl()
{

}

LevelUpUICtrl::~LevelUpUICtrl()
{

}




void LevelUpUICtrl::Start()
{
	UIBase::Start();

	LoadImageRes();
	CreateGrowInfoRender();
	CreateNewSkillBoardRender();
	CreateLevelText();
	CreateSkillInfoText();
	
	DataMgr::PushLevelUpCallBack(std::bind(&LevelUpUICtrl::LevelUpCallBack, this));
}



void LevelUpUICtrl::LoadImageRes()
{
	static bool IsLoad = false;
	if (true == IsLoad)
		return;

	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("UI");
	Dir.Move("LevelUp");
	GameEngineTexture::Load(Dir.GetPlusFileName(GrowthInfo_FileName).GetFullPath());
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName(NewSkillBoard_FileName).GetFullPath());

	Dir.Move("LevelUpUI_AcquireSkillInfoes");
	std::vector<GameEngineFile> Files = Dir.GetAllFile({".png"});
	for (const GameEngineFile& File : Files)
	{
		GameEngineTexture::Load(File.GetFullPath());
	}

	IsLoad = true;
}



void LevelUpUICtrl::CreateGrowInfoRender()
{
	GrowthBox = CreateComponent<GameEngineUIRenderer>(FieldUIRenderOrder::EventInfo);
	GrowthBox->SetScaleToTexture(GrowthInfo_FileName);

	GrowthBox->GetTransform()->SetLocalPosition(GrowBoxPoses.first);
	GrowthBox->Off();
	//GrowthBox->ColorOptionValue.MulColor.a = 0.5f;
}



void LevelUpUICtrl::CreateNewSkillBoardRender()
{
	const float4 Offset = float4{ -380.f, -190.f };

	NewSkillBox = CreateComponent<GameEngineUIRenderer>(FieldUIRenderOrder::EventInfo);
	NewSkillBox->CreateAnimation
	({
		.AnimationName = NewSkillBoard_FileName,
		.SpriteName = NewSkillBoard_FileName,
		.Loop = false,
		.ScaleToImage = true,
	});

	NewSkillBox->ChangeAnimation(NewSkillBoard_FileName);
	NewSkillBox->GetTransform()->SetLocalPosition(Offset);
	NewSkillBox->Off();
	//NewSkillBox->ColorOptionValue.MulColor.a = 0.5f;
}

void LevelUpUICtrl::CreateLevelText()
{
	const float4 Offset = float4{ -0.2f, 0.07f };
	const std::string_view FontName = "»ﬁ∏’µ’±Ÿ«ÏµÂ∂Û¿Œ";
	if (nullptr == GameEngineFont::Find(FontName))
	{
		GameEngineFont::Load(FontName);
	}

	LevelText = CreateComponent<UIFontRenderer>(FieldUIRenderOrder::EventInfo);
	LevelText->SetFont(FontName);
	LevelText->SetScale(20.f);
	LevelText->SetText("You Suck");
	LevelText->SetColor(float4::White);
	LevelText->SetFontFlag(FW1_TEXT_FLAG::FW1_LEFT);

	GameEngineTransform* LevelTrans = LevelText->GetTransform();
	LevelTrans->SetParent(GrowthBox->GetTransform(), false);
	LevelTrans->SetLocalPosition(Offset);
}


void LevelUpUICtrl::CreateSkillInfoText()
{
	NewSkillInfoText = CreateComponent<GameEngineUIRenderer>(FieldUIRenderOrder::EventInfo);
	float4 Pos = NewSkillBox->GetTransform()->GetWorldPosition();
	NewSkillInfoText->GetTransform()->SetWorldPosition(Pos);
	NewSkillInfoText->Off();
}



bool LevelUpUICtrl::LevelUpCallBack()
{
	if (GetLevel() != FieldLevelBase::GetPtr().get())
		return false;

	On();
	ResetLiveTime();

	int CurPlayerLevel = DataMgr::GetPlayerLevel();
	GrowthBox->On();
	LevelText->SetText(GameEngineString::ToString(CurPlayerLevel));

	for (size_t i = 0; i < LevelUpSkills.size(); ++i)
	{
		if (LevelUpSkills[i].first != CurPlayerLevel)
			continue;

		NewSkillBox->On();
		NewSkillBox->ChangeAnimation(NewSkillBoard_FileName);
		PlayerStateType AcquireSkill = LevelUpSkills[i].second;
		SkillMgr::AcquireSkill(AcquireSkill);

		const std::string_view& NewSkillTexName = AcquireSkillNames[i];
		NewSkillInfoText->SetScaleToTexture(NewSkillTexName);
		return false;
	}

	return false;
}


void LevelUpUICtrl::Off()
{
	UIBase::Off();

	GrowthBox->Off();
	NewSkillBox->Off();
	NewSkillInfoText->Off();
}



void LevelUpUICtrl::Update(float _DeltaTime)
{
	UIBase::Update(_DeltaTime);

	static const float WaitTime = 3.f;
	if (WaitTime < GetLiveTime())
	{
		Off();
		return;
	}

	Update_GrowthInfo(_DeltaTime);
	Update_NewSkill(_DeltaTime);
}

void LevelUpUICtrl::Update_GrowthInfo(float _DeltaTime)
{
	if (false == GrowthBox->IsUpdate())
		return;

	static const float Duration = 0.5f;
	
	float Ratio = GetLiveTime() / Duration;
	float4 NextPos = float4::LerpClamp(GrowBoxPoses.first, GrowBoxPoses.second, Ratio);
	GrowthBox->GetTransform()->SetLocalPosition(NextPos);
}

void LevelUpUICtrl::Update_NewSkill(float _DeltaTime)
{
	if (false == NewSkillBox->IsUpdate())
		return;

	if (false == NewSkillBox->IsAnimationEnd())
		return;

	//NewSkillBox->ColorOptionValue.MulColor.a = 0.5f;
	NewSkillInfoText->On();
}


void LevelUpUICtrl::LevelChangeEnd()
{
	UIBase::LevelChangeEnd();
	Off();
}