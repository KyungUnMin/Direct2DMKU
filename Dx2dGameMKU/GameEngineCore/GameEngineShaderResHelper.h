#pragma once
#include "GameEngineConstantBuffer.h"
#include "GameEngineTexture.h"


/*
	���̴� ������ ��ᰡ �Ǵ� �͵���
	SetterŬ������ ����Ű�� �ְ� �Ǵµ�,
	�� SetterŬ�������� ��� �� Ŭ������ ��ӹ޴´�
*/
class GameEngineShaderResources
{
public:
	std::string Name;
	class GameEngineShader* ParentShader = nullptr;
	//b0, t0���� ���° ���Կ� ���õǾ�� �ϴ����� ���� ����
	int BindPoint = -1;

public:
	virtual void Setting() = 0;
};

//-------------------------Setter-----------------------


class GameEngineConstantBufferSetter : public GameEngineShaderResources
{
public:
	std::shared_ptr<GameEngineConstantBuffer> Res;
	const void* CPUData = nullptr;
	size_t CPUDataSize = 0;

	//�� ��������� ���� �簻���ϰ� �ش� ������۰� ���̴� ���� � �������� �����Ѵ�
	void Setting() override;
};


class GameEngineTextureSetter : public GameEngineShaderResources
{
public:
	std::shared_ptr<GameEngineTexture> Res;


	void Setting() override{}
};




//-------------------------Helper-----------------------

class GameEngineShaderResHelper
{
private:
	// GameEngineDevice::GetContext()->VSSetConstantBuffers();
	// GameEngineDevice::GetContext()->PSSetConstantBuffers();
	//���� ���� ������۸� ������ ���ؽ����̴��� �ȼ����̴��� �и��Ǿ� �ִ�.
	// �׿����� ���̴� ���Ͽ����� ���ؽ����̴��� �ȼ����̴��� Input ������� ��ĥ���� �ִ�
	//������ ���ؽ� ���̴��� �ȼ� ���̴��� ������ �̸��� ���� ��츦 ����ؼ�
	//��Ƽ������ �������
	std::multimap<std::string, GameEngineConstantBufferSetter> ConstantBuffer;

public:
	//�ڷᱸ���� ����
	void CreateConstantBufferSetter(const GameEngineConstantBufferSetter& _Buffer)
	{
		ConstantBuffer.insert(std::make_pair(_Buffer.Name, _Buffer));
	}



	//��Ƽ�ʾȿ� ���ڷ� ���� �̸��� ������۰� �ִ��� Ȯ���ϴ� �Լ�
	bool IsConstantBufferSetter(const std::string_view& _Name)
	{
		std::string UpperName = GameEngineString::ToUpper(_Name);
		std::multimap<std::string, GameEngineConstantBufferSetter>::iterator FindIter = ConstantBuffer.find(UpperName);

		if (ConstantBuffer.end() == FindIter)
			return false;

		return true;
	}


	template <typename DataType>
	void SetConstantBufferLink(const std::string_view& _Name, const DataType& _Data)
	{
		SetConstantBufferLink(_Name, reinterpret_cast<const void*>(&_Data), sizeof(DataType));
	}

	//CPU�� ���� GPU�� ������� ���� ������Ű�� �Լ�
	void SetConstantBufferLink(const std::string_view& _Name, const void* _Data, size_t _Size);


	/*���� ���ĸ� �� �� ���������� �ٸ� ����� �ؽ�ó�� �־��ֱ� ����
		�׷��� Copy�� ���� ���̴� ���ҽ� ���ۿ� �ִ� ���͵��� ���� �Ѵ�
		���̴� �ȿ� �ִ� ���ҽ����۴� ���÷����� �� � ���۵��� ����ߴ��� ���縸 �ϱ� ����*/
	void Copy(const GameEngineShaderResHelper& _ResHelper);


	//�ڽ� �ȿ� �ִ� ������ۼ��͵��� Setting�Լ����� ȣ������ش�
	void Setting();
};