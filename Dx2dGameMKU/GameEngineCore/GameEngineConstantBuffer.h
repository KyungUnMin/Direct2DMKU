#pragma once
#include "GameEngineResource.h"
#include "GameEngineDirectBuffer.h"

/*
	���̴� ���Ͽ� ������� �Է��� �� ���Ǵ�
	������۸� �����ϴ� Ŭ�����̴�.
	������۰� ���̴� ���ϸ��� �����ϸ�
	�޸� �����̱� ������
	���� ũ���� ������۵��� ��Ȱ���ϰ� �ȴ�
*/

class GameEngineConstantBuffer : public GameEngineResource<GameEngineConstantBuffer>, public GameEngineDirectBuffer
{
public:
	GameEngineConstantBuffer();
	~GameEngineConstantBuffer() override;

	GameEngineConstantBuffer(const GameEngineConstantBuffer& _Other) = delete;
	GameEngineConstantBuffer(GameEngineConstantBuffer&& _Other) noexcept = delete;
	GameEngineConstantBuffer& operator=(const GameEngineConstantBuffer& _Other) = delete;
	GameEngineConstantBuffer& operator=(const GameEngineConstantBuffer&& _Other) noexcept = delete;

	static std::shared_ptr<GameEngineConstantBuffer> CreateAndFind(
		int _Byte, const std::string_view& _Name, 
		const D3D11_SHADER_BUFFER_DESC& _BufferDesc)
	{
		//�ش� ũ���� ������۰� �������� �ʴ´ٸ� ������ �����
		if (ConstantBufferRes.end() == ConstantBufferRes.find(_Byte))
		{
			ConstantBufferRes[_Byte];
		}

		std::string UpperName = GameEngineString::ToUpper(_Name.data());

		//�̸����� ã������ �ִٸ� �� ���۸� ��Ȱ���Ѵ�.
		if (ConstantBufferRes[_Byte].end() != ConstantBufferRes[_Byte].find(UpperName))
		{
			return ConstantBufferRes[_Byte][UpperName];
		}

		//���۸� ���� ����� �ʱ� �������ش�
		std::shared_ptr<GameEngineConstantBuffer> Buffer = CreateUnNamed();
		ConstantBufferRes[_Byte][UpperName] = Buffer;
		Buffer->ResCreate(_BufferDesc);

		return Buffer;
	}

	//static ��������� map ����
	static void ResourcesClear();

protected:
	//���� ������� ���۸� �ʱ⼼���Ѵ�(ũ��, ������� ǥ��, GPU ��������)
	void ResCreate(const D3D11_SHADER_BUFFER_DESC& _BufferDesc);

private:
	//<��� ���� ũ��, <�̸�, ������>>
	static std::map<int, std::map<std::string, std::shared_ptr<GameEngineConstantBuffer>>> ConstantBufferRes;
};

