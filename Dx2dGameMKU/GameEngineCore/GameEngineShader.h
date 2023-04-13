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

	//���� : � ���̴� Ÿ������(���ؽ� ���̴��� vs, �ȼ� ���̴��� ps), 5.0����
	void CreateVersion(const std::string_view& _ShaderType, UINT _VersionHigh = 5, UINT _VersionLow = 0);

	//���̴� ������ main�Լ��� ����
	inline void SetEntryPoint(const std::string_view& _EntryPoint)
	{
		EntryPoint = _EntryPoint;
	}

protected:
	//���̴� �ڵ带 2�� �����ͷ� �����Ͽ�
	//�׷��� ī�忡 ���������� �޴� �ڵ鷯
	ID3DBlob* BinaryCode = nullptr;
	std::string Version = "";

	//���̴� ������ main�Լ���
	std::string EntryPoint = "";

private:
	
};

