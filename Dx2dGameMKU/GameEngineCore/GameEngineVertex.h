#pragma once
#include <GameEngineBase/GameEngineMath.h>

//���̴� ������ �ø�ƽ ������ ����ϱ� ���� ����ؾ� �ϴ� ������ ���� Ŭ����
class GameEngineInputLayOutInfo
{
public:
	static UINT FormatSize(DXGI_FORMAT _Format);

	inline const std::vector<D3D11_INPUT_ELEMENT_DESC>& GetDescs()
	{
		return Descs;
	}

private:
	std::vector<D3D11_INPUT_ELEMENT_DESC> Descs;
	int Offset = 0;

public:
	void AddInputLayOut(
		LPCSTR _SemanticName,					// �ø�ƽ�� � �ڷ������� ���(POSITION or COLOR...)
		DXGI_FORMAT _Format,					// �ڷ����� ũ��
		D3D11_INPUT_CLASSIFICATION _InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA, // ���ؽ� �����Ͱ� �ν��Ͻ� ���������� �ǹ�
		UINT _InstanceDataStepRate = 0, // �ν��Ͻ��̶�� ������ ��ﶧ ����.
		UINT _AlignedByteOffset = -1,		// 0��° ����Ʈ���� 
		UINT _InputSlot = 0,						// n���� ���ؽ� ���۸� �����Ҷ� n��° ���ؽ� ������ ��ǲ ���̾ƿ����� ǥ��
		UINT _SemanticIndex = 0				//�ø�ƽ ������ ������ �־��� �� �ִµ� �� ���������� ������ �ϳ��� ����
	);
};


class GameEngineVertex
{
public:
	//���� �����ϰ� �ִµ�, ���̾ƿ� ������ ���ؽ����� �� �ٸ���
	//GameEngineInputLayOutInfo�� ������ ���ؽ����� static���� ��� ��������
	static GameEngineInputLayOutInfo LayOut;

public:
	//�� ���ؽ��� ������ ���̴� ���Ϸ� �̵��ϰ� �� �ٵ�,
	//�� �� �ø�ƽ ����(���̴� ���� Input����ü)�� ������ �޶� �̸��� �Ȱ��ƾ� �Ѵ�, �����ϸ� ������ ���� ����
	float4 POSITION;
	float4 UV;

	//TODO...
};

/*
�ؽ�ó�� �ȼ��� �׸���
	�޽��� �ؽ��� ���
	xy��� ���� ����� 0 ���� �ϴ��� 1�� �����Ѵ�

	�̸� UV��ǥ���� �Ѵ�
	���� ��� (0.75, 0.75)�� �ش� �޽��� �ȼ� ������
	�ؽ����� (0.75, 0.75)�� ������ ��ĥ�Ѵ�

	�̷��� �ȼ� ���̴��� ������� 
	�����ִ� ���� ���÷���� �Ѵ�

	(����� �ȼ� ���̴��� �ڵ����� �������� �ȴ�)
*/
