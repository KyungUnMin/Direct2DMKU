#include "PrecompileHeader.h"
#include "ShaderUIRenderer.h"
#include "RCGEnums.h"

ShaderUIRenderer::ShaderUIRenderer()
{

}

ShaderUIRenderer::~ShaderUIRenderer()
{

}

void ShaderUIRenderer::Start()
{
	PushCameraRender(static_cast<int>(RCG_CamNumType::UI));

	//파이프라인 설정이나 상수버퍼 연결은 외부에서 처리
}
