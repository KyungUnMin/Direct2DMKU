#include "PrecompileHeader.h"
#include "OpeningLevel.h"

#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineTexture.h>

#include "RCGEnums.h"
#include "RCGDefine.h"
#include "OpeningActor.h"

OpeningLevel::OpeningLevel()
{

}

OpeningLevel::~OpeningLevel()
{

}

void OpeningLevel::Start()
{
	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);

	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory(RCGDefine::RootPath);
	Dir.Move(RCGDefine::RootPath);
	Dir.Move(RCGDefine::ImagePath);
	Dir.Move("Opening");

	std::vector<GameEngineFile> Images = Dir.GetAllFile({ ".png" });
	for (const GameEngineFile& Path : Images)
	{
		GameEngineTexture::Load(Path.GetFullPath());
	}

	CreateActor<OpeningActor>(static_cast<int>(Opening_UpdateOrder::BackGround));
}
