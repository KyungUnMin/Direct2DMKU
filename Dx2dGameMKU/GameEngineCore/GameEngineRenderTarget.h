#pragma once
#include "GameEngineRenderer.h"
#include "GameEngineCore.h"

class GameEngineTexture;
class GameEngineRenderTarget;

class GameEnginePostProcess
	: std::enable_shared_from_this<GameEnginePostProcess>
{
	friend GameEngineRenderTarget;

public:
	std::shared_ptr<GameEngineRenderTarget> ResultTarget;

protected:
	virtual void Start(GameEngineRenderTarget* _Target) = 0;
	virtual void Effect(GameEngineRenderTarget* _Target, float _DeltaTime) = 0;
};



//텍스처의 렌더타켓을 이용한 기능들을 처리하는 클래스, 실제 렌더타갯은 텍스처가 가지고 있음
class GameEngineRenderTarget 
	: public GameEngineResource<GameEngineRenderTarget>
	, std::enable_shared_from_this<GameEngineRenderTarget>
{
	friend class GameEngineCore;

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


	static std::shared_ptr<GameEngineRenderTarget> Create(DXGI_FORMAT _Format, float4 _Scale, float4 _Color)
	{
		std::shared_ptr<GameEngineRenderTarget> NewRenderTarget = GameEngineResource::CreateUnNamed();
		NewRenderTarget->ResCreate(_Format, _Scale, _Color);
		return NewRenderTarget;
	}


	//렌더타겟이 가르키고 있는 이미지를 지우고 깊이버퍼도 초기화한다
	void Clear();

	//랜파에서 아웃풋 머저를 위한 렌더타겟뷰를 세팅해주는 단계(Core의 RenderStart에서 호출)
	void Setting() override;

	//랜더링 파이프라인에 있는 렌더타겟들을 nullptr로 바꾸기(비디오때문에 만든 임시기능)
	void Reset();

	//사전에 만든 텍스처를 바탕으로 깊이버퍼텍스처 만들기, (아직까진) 디바이스에서만 호출됨
	void CreateDepthTexture(int _Index = 0);

	//이미지 덮어쓰기
	void Merge(std::shared_ptr<GameEngineRenderTarget> _Other, size_t _Index = 0);



	//이 렌더타겟에 포스트 프로세싱 이펙트 만들기
	template<typename EffectType>
	std::shared_ptr<EffectType> CreateEffect()
	{
		std::shared_ptr<EffectType> Effect = std::make_shared<EffectType>();
		EffectInit(Effect);
		Effects.push_back(Effect);
		return Effect;
	}

	//포스트 프로세싱 제거
	void ReleaseEffect(std::shared_ptr<GameEnginePostProcess> _Effect);

	//포스트 프로세싱 실행
	void Effect(float _DeltaTime);

	std::shared_ptr<GameEngineTexture> GetTexture(int _Index)
	{
		return Textures[_Index];
	}

	void DepthSettingOn()
	{
		DepthSetting = true;
	}

	void DepthSettingOff()
	{
		DepthSetting = false;
	}

protected:

private:
	//MergeUnit에 머지용 렌더링 파이프라인 세팅
	static void RenderTargetUnitInit();
	//머지렌더(이미지 복사)를 도와주는 정적 개체
	static GameEngineRenderUnit MergeUnit;


	//깊이버퍼 활성화 유무
	bool DepthSetting = true;


	float4 Color = float4{ 0.f, 0.f, 0.f, 0.f };

	//이 렌더타겟에 포스트프로세싱을 적용할 이펙트들
	std::vector<std::shared_ptr<GameEnginePostProcess>> Effects;

	std::vector<std::shared_ptr<GameEngineTexture>> Textures;
	std::vector<ID3D11RenderTargetView*> RTVs;


	//깊이버퍼용 텍스처
	std::shared_ptr<GameEngineTexture> DepthTexture;

	//텍스처의 경우엔 포인터를 두개로 나눠서
	//GameEngineTexture와 GameEngineRenderTarget이 각각 한개씩 나눠갖는다
	void ResCreate(std::shared_ptr<GameEngineTexture> _Texture, float4 _Color);


	void ResCreate(DXGI_FORMAT _Format, float4 _Scale, float4 _Color);

	//GameEnginePostProcess Start 호출
	void EffectInit(std::shared_ptr<GameEnginePostProcess> _PostProcess);
};

