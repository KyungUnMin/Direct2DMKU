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
};

//-------------------------Setter-----------------------


class GameEngineTextureSetter : public GameEngineShaderResources
{
public:
	std::shared_ptr<GameEngineTexture> Res;
};


class GameEngineConstantBufferSetter : public GameEngineShaderResources
{
public:
	std::shared_ptr<GameEngineConstantBuffer> Res;
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
	//��Ƽ������ �������(�ϴ� ���ݴ� �ϼ��Ǿ�� �� �� ������ ����)
	std::multimap<std::string, GameEngineConstantBufferSetter> ConstantBuffer;

public:
	//�ڷᱸ���� ����
	void CreateConstantBufferSetter(const GameEngineConstantBufferSetter& _Buffer)
	{
		ConstantBuffer.insert(std::make_pair(_Buffer.Name, _Buffer));
	}

	//����? ���� ���� ����?
	void Copy(const GameEngineShaderResHelper& _ResHelper);
};