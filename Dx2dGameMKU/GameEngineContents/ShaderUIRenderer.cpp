#include "PrecompileHeader.h"
#include "ShaderUIRenderer.h"

ShaderUIRenderer::ShaderUIRenderer()
{

}

ShaderUIRenderer::~ShaderUIRenderer()
{

}

void ShaderUIRenderer::Start()
{
	PushCameraRender(100);

	//파이프라인 설정이나 상수버퍼 연결은 외부에서 처리
}
