#pragma once
#include "GameEngineComponent.h"
#include "GameEngineShader.h"

class GameEngineRenderer : public GameEngineComponent
{
public:
	GameEngineRenderer();
	~GameEngineRenderer() override;

	GameEngineRenderer(const GameEngineRenderer& _Other) = delete;
	GameEngineRenderer(GameEngineRenderer&& _Other) noexcept = delete;
	GameEngineRenderer& operator=(const GameEngineRenderer& _Other) = delete;
	GameEngineRenderer& operator=(const GameEngineRenderer&& _Other) noexcept = delete;

	//(��ο�(�׸���) �ϱ� ������ ���̴� ���Ͽ� ���� �־��ִ� �� ����)
	//������������ �����ϸ鼭, ���̴� �������� ���͵��� �Ѱ��� ������
	void SetPipeLine(const std::string_view& _Name);

	inline GameEngineShaderResHelper& GetShaderResHelper()
	{
		return ShaderResHelper;
	}

protected:
	void Render(float _DeltaTime) override;

private:
	std::shared_ptr<class GameEngineRenderingPipeLine> Pipe;

	/*
		����Ƽ�� �𸮾� ���� ���������� ���� ���͵���
		����� ������������ �����Ѵ�.
		�׷��� �� ������������ ������� �ϳ��� �ٲ㵵
		�ش� ������������ ����ϰ� �ִ� ���͵��� ���� �ٲ��.

		�� ���� ���������� �װͰ��� �ٸ���
		���������� ������ �������, �ؽ�ó���� ���� �ߴ�.
		������ �� ���̴� ������ ���÷����� ���� �����ؼ�
		� ���ҽ����� ���Ǿ����� �˾Ƴ���,
		�׿� ���� ������ ������ ������������ ���õɶ�
		GameEngineShaderResHelper::Copy�Լ��� ���� �����ؿ´�
		�׷��� ����� ���Ϳ� ������ ������ �������, �ؽ�ó ���� ä�������� �ȴ�
	*/
	GameEngineShaderResHelper ShaderResHelper;
};

