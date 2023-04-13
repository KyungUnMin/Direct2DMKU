#pragma once
#include "GameEngineResource.h"
#include "GameEngineShader.h"

class GameEngineVertexShader : public GameEngineResource<GameEngineVertexShader>, public GameEngineShader
{
public:
	GameEngineVertexShader();
	~GameEngineVertexShader() override;

	GameEngineVertexShader(const GameEngineVertexShader& _Other) = delete;
	GameEngineVertexShader(GameEngineVertexShader&& _Other) noexcept = delete;
	GameEngineVertexShader& operator=(const GameEngineVertexShader& _Other) = delete;
	GameEngineVertexShader& operator=(const GameEngineVertexShader&& _Other) noexcept = delete;

	//���̴� ������ ��ο� ���̴� ������ �����Լ�, �������� �Է¹޾Ƽ� ���̴� ������ �������ϰ� �ڵ鷯�� �޾ƿ´�(�̸��� �ڵ����� ���� ���� �ּҸ����� ����)
	static std::shared_ptr<GameEngineVertexShader> Load(const std::string_view& _Path, const std::string_view& _EntryPoint, UINT _VersionHigh = 5, UINT _VersionLow = 0)
	{
		GameEnginePath Path = GameEnginePath(std::string(_Path.data()));
		//�� �Լ��� �Ȱ����� �̸��� ������ ���� ��η� ����, 
		return Load(_Path, Path.GetFileName(), _EntryPoint, _VersionHigh, _VersionLow);
	}

	//���̴� ������ ��ο� �� ��ü�� �̸�, ���̴� ������ �����Լ�, �������� �Է¹޾Ƽ� ���̴� ������ �������ϰ� �ڵ鷯�� �޾ƿ´�
	static std::shared_ptr<GameEngineVertexShader> Load(const std::string_view& _Path, const std::string_view& _Name, const std::string_view& _EntryPoint, UINT _VersionHigh = 5, UINT _VersionLow = 0)
	{
		std::shared_ptr<GameEngineVertexShader> Res = GameEngineResource::Create(_Name);
		Res->ShaderLoad(_Path, _EntryPoint, _VersionHigh, _VersionLow);
		return Res;
	}

	//���ؽ� ���̴� ����
	void Setting() override;

protected:

private:
	//GPU�� ������ ���̴� ���̳ʸ� �ڵ��� �ڵ鷯
	ID3D11VertexShader* ShaderPtr = nullptr;

	//���̴����� ������ �� GPU�� �����ϱ�
	void ShaderLoad(const std::string_view& _Path, const std::string_view& _EntryPoint, UINT _VersionHigh = 5, UINT _VersionLow = 0);
};

