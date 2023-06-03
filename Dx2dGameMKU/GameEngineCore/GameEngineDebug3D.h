#pragma once
#include "GameEngineCamera.h"
#include "GameEngineTransform.h"

namespace GameEngineDebug
{
	void DrawBox(class GameEngineCamera* _Cam, class GameEngineTransform* _Trans, float4 Color = float4::Green);

	void DrawSphere(class GameEngineCamera* _Cam, class GameEngineTransform* _Trans, float4 Color = float4::Green);

	void DebugRender(class GameEngineCamera* _Cam, float _Delta);
};

