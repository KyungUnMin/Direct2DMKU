#pragma once
#include "GameEngineTexture.h"

//텍스처의 렌더타켓을 이용한 기능들을 처리하는 클래스, 실제 렌더타갯은 텍스처가 가지고 있음
class GameEngineRenderTarget : public GameEngineResource<GameEngineRenderTarget>
{
public:
	GameEngineRenderTarget();
	~GameEngineRenderTarget() override;

	GameEngineRenderTarget(const GameEngineRenderTarget& _Other) = delete;
	GameEngineRenderTarget(GameEngineRenderTarget&& _Other) noexcept = delete;
	GameEngineRenderTarget& operator=(const GameEngineRenderTarget& _Other) = delete;
	GameEngineRenderTarget& operator=(const GameEngineRenderTarget&& _Other) noexcept = delete;

	//이름, 이 렌더타겟이 가리키게 될 텍스처, Clear시 초기화 시킬 색상
	static std::shared_ptr<GameEngineRenderTarget> Create(const std::string_view& _Name, std::shared_ptr<GameEngineTexture> _Texture, float4 _Color)
	{
		//부모의 함수를 통해 자신 생성
		std::shared_ptr<GameEngineRenderTarget> NewRenderTarget = GameEngineResource<GameEngineRenderTarget>::Create(_Name);

		//인자 초기화
		NewRenderTarget->Create(_Texture, _Color);
		return NewRenderTarget;
	}

	//렌더타겟이 가르키고 있는 이미지를 지운다
	void Clear();

protected:

private:
	float4 Color = float4{ 0.f, 0.f, 0.f, 0.f };
	std::shared_ptr<GameEngineTexture> Texture = nullptr;

	//텍스처의 경우엔 포인터를 두개로 나눠서
	//GameEngineTexture와 GameEngineRenderTarget이 각각 한개씩 나눠갖는다
	void Create(std::shared_ptr<GameEngineTexture> _Texture, float4 _Color);
};

