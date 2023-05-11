#include "PrecompileHeader.h"
#include "TestLevel.h"

#include <GameEngineCore/GameEngineCamera.h>

TestLevel::TestLevel()
{

}

TestLevel::~TestLevel()
{

}

#include "BossIntroMovie.h"
#include "RCGEnums.h"

void TestLevel::Start()
{
	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
	CreateActor<BossIntroMovie>(static_cast<int>(UpdateOrder::UI))->Init(MovieType::School);
}

void TestLevel::Update(float _DelatTime)
{

}
