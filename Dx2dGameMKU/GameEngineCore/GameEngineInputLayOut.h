#pragma once
#include "GameEngineResource.h"


//���̴� ������ �ø�ƽ ������ ���� �־��ִ� �ڷ����� ������Ű�� ���� ���� ����(��ǲ �����1)
class GameEngineInputLayOut : public GameEngineResource<GameEngineInputLayOut>
{
public:
	GameEngineInputLayOut();
	~GameEngineInputLayOut() override;

	GameEngineInputLayOut(const GameEngineInputLayOut& _Other) = delete;
	GameEngineInputLayOut(GameEngineInputLayOut&& _Other) noexcept = delete;
	GameEngineInputLayOut& operator=(const GameEngineInputLayOut& _Other) = delete;
	GameEngineInputLayOut& operator=(const GameEngineInputLayOut&& _Other) noexcept = delete;

	void Release();

	//���̾ƿ��� ����� ���ؼ��� ���ؽ� ���ۿ� �ִ� ���̾ƿ� ������ ���ؽ� ���̴��� ���̳ʸ� �ڵ带 �˾ƾ� �Ѵ�
	void ResCreate(std::shared_ptr<class GameEngineVertexBuffer> _Info, std::shared_ptr<class GameEngineVertexShader> _Shader);

	//GPU�� ���̾ƿ� ������ ����
	void Setting() override;

	inline bool IsCreate() const
	{
		return (nullptr != InputLayOut);
	}

protected:

private:
	ID3D11InputLayout* InputLayOut = nullptr;
};

