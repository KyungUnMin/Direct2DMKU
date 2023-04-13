#pragma once
#include <GameEngineBase/GameEngineMath.h>

//���̴� ������ �ø�ƽ ������ ����ϱ� ���� ����ؾ� �ϴ� ������ ���� Ŭ����
class GameEngineInputLayOut
{
private:
	std::vector<D3D11_INPUT_ELEMENT_DESC> Descs;

public:
	void AddInputLayOut(
		LPCSTR _SemanticName,					// �ø�ƽ�� � �ڷ������� ���(POSITION or COLOR...)
		DXGI_FORMAT _Format,					// �ڷ����� ũ��
		D3D11_INPUT_CLASSIFICATION _InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA, // ���ؽ� �����Ͱ� �ν��Ͻ� ���������� �ǹ�
		UINT _InstanceDataStepRate = 0, // �ν��Ͻ��̶�� ������ ��ﶧ ����.
		UINT _AlignedByteOffset = -1,		// 0��° ����Ʈ���� 
		UINT _InputSlot = 0,						// n���� ���ؽ� ���۸� �����Ҷ� n��° ���ؽ� ������ ��ǲ ���̾ƿ����� ǥ��
		UINT _SemanticIndex = 0
	);
};


class GameEngineVertex
{
public:
	static GameEngineInputLayOut LayOut;

public:
	//��ġ��
	float4 POSITION;
	//���� ����
	float4 COLOR;

	//TODO...
};


