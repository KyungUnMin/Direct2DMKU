#pragma once
#include "GameEngineEnum.h"
#include "GameEngineShaderResHelper.h"

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

	inline const GameEngineShaderResHelper& GetShaderResHelper() const
	{
		return ResHelper;
	}

	inline ShaderType GetType() const
	{
		return Type;
	}

	static void AutoCompile(GameEngineFile& _File);

protected:
	ShaderType Type = ShaderType::None;

	//���̴� �ڵ带 2�� �����ͷ� �����Ͽ�
	//�׷��� ī�忡 ���������� �޴� �ڵ鷯
	ID3DBlob* BinaryCode = nullptr;
	std::string Version = "";

	//���̴� ������ main�Լ���
	std::string EntryPoint = "";


	//���̴� ������ ������ �ϰ� �� �� ���÷����� ���� ���� ������ ���ҽ��� ����/�����ϱ�
	void ShaderResCheck();

private:
	/*
		GameEngineShader������ ����
			���̴� ������ � ���ҽ� ����(������۳� �ؽ�ó��)���� ����ϴ��� ���
		GameEngineRender������ ����
			������ ������������ ���õɶ� GameEngineShader�鿡 �ִ� ������ Copy��
	*/
	GameEngineShaderResHelper ResHelper;
};

