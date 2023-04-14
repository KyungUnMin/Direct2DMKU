#include "PrecompileHeader.h"
#include "GameEngineInputLayOut.h"
#include "GameEngineVertex.h"
#include "GameEngineVertexBuffer.h"
#include "GameEngineVertexShader.h"

GameEngineInputLayOut::GameEngineInputLayOut()
{

}

GameEngineInputLayOut::~GameEngineInputLayOut()
{
	Release();
}

void GameEngineInputLayOut::Release()
{
	if (nullptr != InputLayOut)
	{
		InputLayOut->Release();
		InputLayOut = nullptr;
	}
}

void GameEngineInputLayOut::ResCreate(std::shared_ptr<class GameEngineVertexBuffer> _Info, std::shared_ptr<class GameEngineVertexShader> _Shader)
{
	//���ؽ� ���̴� ������ �ٲ���� ����ؼ�
	//�̹� ��������ٸ� ����� �ٽ� �����
	Release();

	if (nullptr == _Info->LayOutInfo)
	{
		//����� ��� ���ؽ����� ��ǲ ���̾ƿ� ������ ������ �־�� �ϸ�
		//���ؽ� ���۸� ������ �� �ش� ���ؽ��� ��ǲ���̾ƿ� ������ ����Ű�� �ȴ�
		MsgAssert("���̾ƿ� ������ ����� ���� ���ؽ� �����Դϴ�");
		return;
	}

	const std::vector<D3D11_INPUT_ELEMENT_DESC>& LayOutInfoes = _Info->LayOutInfo->GetDescs();

	HRESULT Result = GameEngineDevice::GetDevice()->CreateInputLayout(
		&LayOutInfoes[0],
		static_cast<UINT>(LayOutInfoes.size()),
		_Shader->BinaryCode->GetBufferPointer(),
		_Shader->BinaryCode->GetBufferSize(),
		&InputLayOut);

	if (S_OK != Result)
	{
		MsgAssert("��ǲ ���̾ƿ� ������ �����߽��ϴ�");
		return;
	}
}

void GameEngineInputLayOut::Setting()
{
	if (nullptr == InputLayOut)
	{
		MsgAssert("�������� ���� ��ǲ���̾ƿ��� �����Ϸ��� �߽��ϴ�.");
	}

	GameEngineDevice::GetContext()->IASetInputLayout(InputLayOut);
}
