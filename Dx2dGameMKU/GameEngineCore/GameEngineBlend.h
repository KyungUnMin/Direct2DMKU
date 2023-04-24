#pragma once
#include "GameEngineResource.h"

/*
	�ƿ�ǲ ���� �ܰ迡��
		�ҽ��÷��� ������ �÷��� ��� ��ĥ���� ���� ���(���ϱ�, ���� ���)
		�ҽ� �÷� : �� ����Ÿ�ٿ� �߰��� ����
		������ �÷� : ������ �־��� ����
*/
class GameEngineBlend : public GameEngineResource<GameEngineBlend>
{
public:
	GameEngineBlend();
	~GameEngineBlend() override;

	GameEngineBlend(const GameEngineBlend& _Other) = delete;
	GameEngineBlend(GameEngineBlend&& _Other) noexcept = delete;
	GameEngineBlend& operator=(const GameEngineBlend& _Other) = delete;
	GameEngineBlend& operator=(const GameEngineBlend&& _Other) noexcept = delete;

	static std::shared_ptr<GameEngineBlend> Create(const std::string_view& _Name, const D3D11_BLEND_DESC& _Desc)
	{
		std::shared_ptr<GameEngineBlend> Res = GameEngineResource::Create(_Name);
		Res->ResCreate(_Desc);
		return Res;
	}

	void Setting() override;

protected:

private:
	D3D11_BLEND_DESC Desc = {};
	ID3D11BlendState* State = nullptr;

	//2�ڸ��� ��� ���� ���带 ������ ����
	UINT Mask = 0xFFFFFFFF;

	void ResCreate(const D3D11_BLEND_DESC& _Value);
};

