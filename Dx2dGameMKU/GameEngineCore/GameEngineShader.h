#pragma once


class GameEngineShader
{
public:
	GameEngineShader();
	~GameEngineShader();

	GameEngineShader(const GameEngineShader& _Other) = delete;
	GameEngineShader(GameEngineShader&& _Other) noexcept = delete;
	GameEngineShader& operator=(const GameEngineShader& _Other) = delete;
	GameEngineShader& operator=(const GameEngineShader&& _Other) noexcept = delete;

protected:

private:
	//���̴� �ڵ带 2�� �����ͷ� �����Ͽ�
	//�׷��� ī�忡 ���������� �޴� �ڵ鷯
	ID3DBlob* BinaryCode = nullptr;
	std::string Version;
};

