#pragma once
#include "GameEngineResource.h"
#include "GameEngineShader.h"

class GameEnginePixelShader : public GameEngineResource<GameEnginePixelShader>, public GameEngineShader
{
public:
	GameEnginePixelShader();
	~GameEnginePixelShader() override;

	GameEnginePixelShader(const GameEnginePixelShader& _Other) = delete;
	GameEnginePixelShader(GameEnginePixelShader&& _Other) noexcept = delete;
	GameEnginePixelShader& operator=(const GameEnginePixelShader& _Other) = delete;
	GameEnginePixelShader& operator=(const GameEnginePixelShader&& _Other) noexcept = delete;


	//���̴� ������ ��ο� ���̴� ������ �����Լ�, �������� �Է¹޾Ƽ� ���̴� ������ �������ϰ� �ڵ鷯�� �޾ƿ´�(�̸��� �ڵ����� ���� ���� �ּҸ����� ����)
	static std::shared_ptr<GameEnginePixelShader> Load(const std::string_view& _Path, const std::string_view& _EntryPoint, UINT _VersionHigh = 5, UINT _VersionLow = 0)
	{
		GameEnginePath Path = GameEnginePath(std::string(_Path.data()));
		//�� �Լ��� �Ȱ����� �̸��� ������ ���� ��η� ����, 
		return Load(_Path, Path.GetFileName(), _EntryPoint, _VersionHigh, _VersionLow);
	}

	//���̴� ������ ��ο� �� ��ü�� �̸�, ���̴� ������ �����Լ�, �������� �Է¹޾Ƽ� ���̴� ������ �������ϰ� �ڵ鷯�� �޾ƿ´�
	static std::shared_ptr<GameEnginePixelShader> Load(const std::string_view& _Path, const std::string_view& _Name, const std::string_view& _EntryPoint, UINT _VersionHigh = 5, UINT _VersionLow = 0)
	{
		std::shared_ptr<GameEnginePixelShader> Res = GameEnginePixelShader::Create(_Name);
		Res->ShaderLoad(_Path, _EntryPoint, _VersionHigh, _VersionLow);
		return Res;
	}

	//�ȼ� ���̴� ����
	void Setting() override;

protected:

private:
	//GPU�� ������ ���̴� ���̳ʸ� �ڵ��� �ڵ鷯
	ID3D11PixelShader* ShaderPtr = nullptr;

	//���̴����� ������ �� GPU�� �����ϱ�
	void ShaderLoad(const std::string_view& _Path, const std::string_view& _EntryPoint, UINT _VersionHigh = 5, UINT _VersionLow = 0);
};

