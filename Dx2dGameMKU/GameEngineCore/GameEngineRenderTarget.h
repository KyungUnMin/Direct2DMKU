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



//�ؽ�ó�� ����Ÿ���� �̿��� ��ɵ��� ó���ϴ� Ŭ����, ���� ����Ÿ���� �ؽ�ó�� ������ ����
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

	//�̸�, �� ����Ÿ���� ����Ű�� �� �ؽ�ó, Clear�� �ʱ�ȭ ��ų ����
	static std::shared_ptr<GameEngineRenderTarget> Create(const std::string_view& _Name, std::shared_ptr<GameEngineTexture> _Texture, float4 _Color)
	{
		//�θ��� �Լ��� ���� �ڽ� ����
		std::shared_ptr<GameEngineRenderTarget> NewRenderTarget = GameEngineResource<GameEngineRenderTarget>::Create(_Name);

		//���� �ʱ�ȭ
		NewRenderTarget->ResCreate(_Texture, _Color);
		return NewRenderTarget;
	}


	static std::shared_ptr<GameEngineRenderTarget> Create(DXGI_FORMAT _Format, float4 _Scale, float4 _Color)
	{
		std::shared_ptr<GameEngineRenderTarget> NewRenderTarget = GameEngineResource::CreateUnNamed();
		NewRenderTarget->ResCreate(_Format, _Scale, _Color);
		return NewRenderTarget;
	}


	//����Ÿ���� ����Ű�� �ִ� �̹����� ����� ���̹��۵� �ʱ�ȭ�Ѵ�
	void Clear();

	//���Ŀ��� �ƿ�ǲ ������ ���� ����Ÿ�ٺ並 �������ִ� �ܰ�(Core�� RenderStart���� ȣ��)
	void Setting() override;

	//������ ���������ο� �ִ� ����Ÿ�ٵ��� nullptr�� �ٲٱ�(���������� ���� �ӽñ��)
	void Reset();

	//������ ���� �ؽ�ó�� �������� ���̹����ؽ�ó �����, (��������) ����̽������� ȣ���
	void CreateDepthTexture(int _Index = 0);

	//�̹��� �����
	void Merge(std::shared_ptr<GameEngineRenderTarget> _Other, size_t _Index = 0);


	//GameEnginePostProcess Start ȣ��
	void EffectInit(std::shared_ptr<GameEnginePostProcess> _PostProcess);

	//�� ����Ÿ�ٿ� ����Ʈ ���μ��� ����Ʈ �����
	template<typename EffectType>
	std::shared_ptr<EffectType> CreateEffect()
	{
		std::shared_ptr<EffectType> Effect = std::make_shared<EffectType>();
		EffectInit(Effect);
		Effects.push_back(Effect);
		return Effect;
	}

	//����Ʈ ���μ��� ����
	void Effect(float _DeltaTime);

	std::shared_ptr<GameEngineTexture> GetTexture(int _Index)
	{
		return Textures[_Index];
	}

protected:

private:
	//MergeUnit�� ������ ������ ���������� ����
	static void RenderTargetUnitInit();
	//��������(�̹��� ����)�� �����ִ� ���� ��ü
	static GameEngineRenderUnit MergeUnit;


	float4 Color = float4{ 0.f, 0.f, 0.f, 0.f };

	//�� ����Ÿ�ٿ� ����Ʈ���μ����� ������ ����Ʈ��
	std::vector<std::shared_ptr<GameEnginePostProcess>> Effects;

	std::vector<std::shared_ptr<GameEngineTexture>> Textures;
	std::vector<ID3D11RenderTargetView*> RTVs;


	//���̹��ۿ� �ؽ�ó
	std::shared_ptr<GameEngineTexture> DepthTexture;

	//�ؽ�ó�� ��쿣 �����͸� �ΰ��� ������
	//GameEngineTexture�� GameEngineRenderTarget�� ���� �Ѱ��� �������´�
	void ResCreate(std::shared_ptr<GameEngineTexture> _Texture, float4 _Color);


	void ResCreate(DXGI_FORMAT _Format, float4 _Scale, float4 _Color);


};

