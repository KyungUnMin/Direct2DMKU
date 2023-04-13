#pragma once
#include "GameEngineTexture.h"

//�ؽ�ó�� ����Ÿ���� �̿��� ��ɵ��� ó���ϴ� Ŭ����, ���� ����Ÿ���� �ؽ�ó�� ������ ����
class GameEngineRenderTarget : public GameEngineResource<GameEngineRenderTarget>
{
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

	//����Ÿ���� ����Ű�� �ִ� �̹����� �����
	void Clear();

	//���Ŀ��� �ƿ�ǲ ������ ���� ����Ÿ�ٺ並 �������ִ� �ܰ�
	void Setting() override;

protected:

private:
	float4 Color = float4{ 0.f, 0.f, 0.f, 0.f };
	std::shared_ptr<GameEngineTexture> Texture = nullptr;

	//�ؽ�ó�� ��쿣 �����͸� �ΰ��� ������
	//GameEngineTexture�� GameEngineRenderTarget�� ���� �Ѱ��� �������´�
	void ResCreate(std::shared_ptr<GameEngineTexture> _Texture, float4 _Color);
};

