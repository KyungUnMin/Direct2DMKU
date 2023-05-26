#pragma once
#include "GameEngineComponent.h"
#include "GameEngineShader.h"

//�������� 1�� �����ϴ� ����
class GameEngineRenderUnit
	:std::enable_shared_from_this<GameEngineRenderUnit>
{
public:
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

public:
	//���������� ���� �G ���̴� ���� ����
	void SetPipeLine(const std::string_view& _Name);
	//������
	void Render(float _DeltaTime);
};

class GameEngineCamera;

class GameEngineRenderer : public GameEngineComponent
{
	friend GameEngineCamera;

public:
	GameEngineRenderer();
	~GameEngineRenderer() override;

	GameEngineRenderer(const GameEngineRenderer& _Other) = delete;
	GameEngineRenderer(GameEngineRenderer&& _Other) noexcept = delete;
	GameEngineRenderer& operator=(const GameEngineRenderer& _Other) = delete;
	GameEngineRenderer& operator=(const GameEngineRenderer&& _Other) noexcept = delete;

	//(��ο�(�׸���) �ϱ� ������ ���̴� ���Ͽ� ���� �־��ִ� �� ����)
	//������������ �����ϸ鼭, ���̴� �������� ���͵��� �Ѱ��� ������
	void SetPipeLine(const std::string_view& _Name, int _index = 0);

	// ���⼭ ���ϵ� ������������ �����ϸ� �� ������������ ����ϴ� ��� �ֵ��� �ٲ�� �ȴ�.
	std::shared_ptr<GameEngineRenderingPipeLine> GetPipeLine(int _index = 0);

	// �̰� ����ϰԵǸ� �� �������� ����Ʈ�� �ڽŸ��� Ŭ�� ������������ ������ �ȴ�.
	std::shared_ptr<GameEngineRenderingPipeLine> GetPipeLineClone(int _index = 0);

	inline GameEngineShaderResHelper& GetShaderResHelper(int _index = 0)
	{
		return Units[_index]->ShaderResHelper;
	}

	inline void CameraCullingOn()
	{
		IsCameraCulling = true;
	}

	//ī�޶��� �������� Z���� ����Ѵ�
	void CalSortZ(GameEngineCamera* _Camera);

protected:
	void Start() override;

	void Render(float _DeltaTime) override;

	//������ _CameraOrder��° ī�޶� �� �������� ���
	void PushCameraRender(int _CameraOrder);

private:
	bool IsCameraCulling = false;

	float CalZ = 0.0f;

	std::vector<std::shared_ptr<GameEngineRenderUnit>> Units;

	//��ϵ� ī�޶� �������� ����� ����Ѵ�
	void RenderTransformUpdate(GameEngineCamera* _Camera);
};

