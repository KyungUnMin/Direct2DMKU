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

	//���������� �����̳� ������� ������ �ܺο��� ó��
}
