#pragma once
#include "GameEngineComponent.h"
#include "GameEngineShader.h"

//�������� 1�� �����ϴ� ����
class GameEngineRenderUnit
{
public:
	std::shared_ptr<class GameEngineRenderingPipeLine > Pipe;
	GameEngineShaderResHelper ShaderResHelper;

public:
	//���������� ���� �G ���̴� ���� ����
	void SetPipeLine(const std::string_view& _Name);
	//������
	void Render(float _DeltaTime);
};


class GameEngineRenderer : public GameEngineComponent
{
	friend class GameEngineCamera;

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

	inline void CameraCullingOn()
	{
		IsCameraCulling = true;
	}

protected:
	void Start() override;

	void Render(float _DeltaTime) override;

	//������ _CameraOrder��° ī�޶� �� �������� ���
	void PushCameraRender(int _CameraOrder);

private:
	bool IsCameraCulling = false;

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

	//��ϵ� ī�޶� �������� ����� ����Ѵ�
	void RenderTransformUpdate(class GameEngineCamera* _Camera);
};

