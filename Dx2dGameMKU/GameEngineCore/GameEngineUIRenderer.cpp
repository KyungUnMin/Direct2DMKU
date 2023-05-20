#include "PrecompileHeader.h"
#include "GameEngineUIRenderer.h"

GameEngineUIRenderer::GameEngineUIRenderer()
{

}

GameEngineUIRenderer::~GameEngineUIRenderer()
{

}

void GameEngineUIRenderer::Start()
{
	PushCameraRender(100);
	SpriteRenderInit();
}
