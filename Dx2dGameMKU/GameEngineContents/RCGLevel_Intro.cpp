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
	//��������, Update�� �ڽ��ʿ��� �θ���  Update�� ȣ����� �־�� �ϰ�,
	GameEngineLevel::Update(_DeltaTime);

	//���� ī�޶� ����϶� �Ȱ��� �����ؼ��� �ȵȴ�(�׷��� �� Update�� �������̵� �� ���� ������?)
	if (true == GetMainCamera()->IsFreeCamera())
		return;

	
}

