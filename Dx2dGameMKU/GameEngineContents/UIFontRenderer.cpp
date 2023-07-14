#include "PrecompileHeader.h"
#include "UIFontRenderer.h"
#include "RCGEnums.h"

UIFontRenderer::UIFontRenderer()
{

}

UIFontRenderer::~UIFontRenderer()
{

}

void UIFontRenderer::Start()
{
	PushCameraRender(static_cast<int>(RCG_CamNumType::UI));
}
