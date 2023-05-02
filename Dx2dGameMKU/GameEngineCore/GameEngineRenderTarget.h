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
		NewRenderTarget->ResCreate(_Texture, _Color);
		return NewRenderTarget;
	}

	//렌더타겟이 가르키고 있는 이미지를 지우고 깊이버퍼도 초기화한다
	void Clear();

	//랜파에서 아웃풋 머저를 위한 렌더타겟뷰를 세팅해주는 단계(Core의 RenderStart에서 호출)
	void Setting() override;

	//랜더링 파이프라인에 있는 렌더타겟들을 nullptr로 바꾸기(비디오때문에 만든 임시기능)
	void Reset();

	//사전에 만든 텍스처를 바탕으로 깊이버퍼텍스처 만들기, (아직까진) 디바이스에서만 호출됨
	void CreateDepthTexture();

protected:

private:
	float4 Color = float4{ 0.f, 0.f, 0.f, 0.f };
	std::shared_ptr<GameEngineTexture> Texture = nullptr;

	//깊이버퍼용 텍스처
	std::shared_ptr<GameEngineTexture> DepthTexture;

	//텍스처의 경우엔 포인터를 두개로 나눠서
	//GameEngineTexture와 GameEngineRenderTarget이 각각 한개씩 나눠갖는다
	void ResCreate(std::shared_ptr<GameEngineTexture> _Texture, float4 _Color);
};

