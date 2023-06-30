#pragma once
#include "GameEngineConstantBuffer.h"
#include "GameEngineTexture.h"
#include "GameEngineSampler.h"


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
	virtual void Reset() {};
};

//-------------------------Setter-----------------------


class GameEngineConstantBufferSetter : public GameEngineShaderResources
{
public:
	std::shared_ptr<GameEngineConstantBuffer> Res;
	const void* CPUData = nullptr;
	UINT CPUDataSize = 0;

	//�� ��������� ���� �簻���ϰ� �ش� ������۰� ���̴� ���� � �������� �����Ѵ�
	void Setting() override;
};


class GameEngineTextureSetter : public GameEngineShaderResources
{
public:
	std::shared_ptr<GameEngineTexture> Res;

	void Setting() override;
	void Reset() override;
};

class GameEngineSamplerSetter : public GameEngineShaderResources
{
public:
	std::shared_ptr<GameEngineSampler> Res;
	void Setting() override;
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
	std::multimap<std::string, GameEngineConstantBufferSetter> ConstantBufferSetters;
	std::multimap<std::string, GameEngineTextureSetter> TextureSetters;
	std::multimap<std::string, GameEngineSamplerSetter> SamplerSetters;

public:
	//���� ���õ� �ؽ�ó�� ���� ���� �߰ߵ� �ؽ�ó�� �޾ƿ���
	GameEngineTextureSetter* GetTextureSetter(const std::string_view& _View);

	//���� ���õ� �ؽ�ó���� �޾ƿ���
	std::vector<GameEngineTextureSetter*> GetTextureSetters(const std::string_view& _View);

	//�ڷᱸ���� ����(���̴����� ���÷������� ���� �����Ҷ� ȣ���)
	void CreateTextureSetter(const GameEngineTextureSetter& _Setter)
	{
		TextureSetters.insert(std::make_pair(_Setter.Name, _Setter));
	}

	void CreateSamplerSetter(const GameEngineSamplerSetter& _Setter)
	{
		SamplerSetters.insert(std::make_pair(_Setter.Name, _Setter));
	}

	void CreateConstantBufferSetter(const GameEngineConstantBufferSetter& _Setter)
	{
		ConstantBufferSetters.insert(std::make_pair(_Setter.Name, _Setter));
	}



	//��Ƽ�ʾȿ� ���ڷ� ���� �̸��� ������۰� �ִ��� Ȯ���ϴ� �Լ�
	bool IsConstantBuffer(const std::string_view& _Name)
	{
		std::string UpperName = GameEngineString::ToUpper(_Name);
		std::multimap<std::string, GameEngineConstantBufferSetter>::iterator FindIter = ConstantBufferSetters.find(UpperName);

		if (ConstantBufferSetters.end() == FindIter)
			return false;

		return true;
	}


	template <typename DataType>
	void SetConstantBufferLink(const std::string_view& _Name, const DataType& _Data)
	{
		SetConstantBufferLink(_Name, reinterpret_cast<const void*>(&_Data), sizeof(DataType));
	}

	// CPU�� ���� GPU�� ������� ���� ������Ű�� �Լ�(���� GPU�� ������� ���� ����� ���� �ƴ�, ������ setting�Լ����� �Ͼ)
	void SetConstantBufferLink(const std::string_view& _Name, const void* _Data, UINT _Size);

	//(�̸�����)�ؽ�ó ����
	void SetTexture(const std::string_view& _SettingName, const std::string_view& _ImageName);

	//�ؽ�ó ���� ����
	void SetTexture(const std::string_view& _SettingName, std::shared_ptr<GameEngineTexture> _Texture);

	/*���� ���ĸ� �� �� ���������� �ٸ� ����� �ؽ�ó�� �־��ֱ� ����
		�׷��� Copy�� ���� ���̴� ���ҽ� ���ۿ� �ִ� ���͵��� ���� �Ѵ�
		���̴� �ȿ� �ִ� ���ҽ����۴� ���÷����� �� � ���۵��� ����ߴ��� ���縸 �ϱ� ����*/
	void Copy(const GameEngineShaderResHelper& _ResHelper);


	//�ڽ� �ȿ� �ִ� ������ۼ��ͳ� �ٸ� ���ҽ����� Setting�Լ����� ȣ������ش�
	void Setting();


	//������ ���������ο��� VS, PS ������ �����Ѵ�
	void AllResourcesReset();
};