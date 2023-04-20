#include "PrecompileHeader.h"
#include "RCGLevel_Intro.h"

#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineCore/GameEngineVideo.h>
#include <GameEngineCore/GameEngineCamera.h>



RCGLevel_Intro::RCGLevel_Intro()
{

}

RCGLevel_Intro::~RCGLevel_Intro()
{

}

void RCGLevel_Intro::Start()
{
	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
	CreateVideo();
	
}

void RCGLevel_Intro::CreateVideo()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResource");
	Dir.Move("ContentsResource");
	std::string Path = Dir.GetPlusFileName("Bossintros_Yamada.avi").GetFullPath();
	Video = GameEngineVideo::Load(Path);
	Video->Play();
}


void RCGLevel_Intro::Update(float _DeltaTime)
{
	//주의하자, Update는 자식쪽에서 부모의  Update를 호출시켜 주어야 하고,
	GameEngineLevel::Update(_DeltaTime);

	//프리 카메라 모드일땐 똑같이 동작해서는 안된다(그런데 이 Update를 오버라이딩 할 일이 많을까?)
	if (true == GetMainCamera()->IsFreeCamera())
		return;

	
}

