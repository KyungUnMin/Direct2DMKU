#pragma once
#include <GameEngineCore/GameEngineSpriteRenderer.h>



/*
	����� ���� ���������� 
	���� �ܺο��� ���� ȣ������־�� �ϴ� ������
*/

enum class RCG_CamNumType;

class SelfRenderer : public GameEngineSpriteRenderer
{
public:
	SelfRenderer();
	~SelfRenderer() override;

	SelfRenderer(const SelfRenderer& _Other) = delete;
	SelfRenderer(SelfRenderer&& _Other) noexcept = delete;
	SelfRenderer& operator=(const SelfRenderer& _Other) = delete;
	SelfRenderer& operator=(const SelfRenderer&& _Other) noexcept = delete;

	
	void SetCamera(RCG_CamNumType _CamType);

	void SetEnginePipe();

protected:
	void Start() override {}

private:

};

