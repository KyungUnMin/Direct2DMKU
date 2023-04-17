#include "PrecompileHeader.h"
#include "GameEngineShader.h"

GameEngineShader::GameEngineShader()
{

}

GameEngineShader::~GameEngineShader()
{
	if (nullptr != BinaryCode)
	{
		BinaryCode->Release();
		BinaryCode = nullptr;
	}
}

void GameEngineShader::CreateVersion(const std::string_view& _ShaderType, UINT _VersionHigh, UINT _VersionLow)
{
	// ���� : vs_5_0
	Version += _ShaderType;
	Version += "_";
	Version += std::to_string(_VersionHigh);
	Version += "_";
	Version += std::to_string(_VersionLow);
}


//���̴� ������ ������ �ϰ� �� �� ���÷����� ���� ������ ������ �Լ�
void GameEngineShader::ShaderResCheck()
{
	if (nullptr == BinaryCode)
	{
		MsgAssert("���̴� ������ ���������� �ʾƼ� ���ҽ��� ������ �� �����ϴ�");
		return;
	}

	//���÷���
	ID3D11ShaderReflection* CompileInfo = nullptr;
	if (S_OK != D3DReflect(BinaryCode->GetBufferPointer(), BinaryCode->GetBufferSize(), IID_ID3D11ShaderReflection,reinterpret_cast<void**>(&CompileInfo)))
	{
		MsgAssert("���̴� ���÷��ǿ� �����Ͽ����ϴ�");
		return;
	}

	D3D11_SHADER_DESC Info;
	CompileInfo->GetDesc(&Info);

	//���̴� ������ ��ǲ ���� �˾ƿ���
	D3D11_SHADER_INPUT_BIND_DESC ResDesc;
	// Info.BoundResources : ���� ����� �������, �ؽ�ó, ���÷����� ����
	for (UINT i = 0; i < Info.BoundResources; ++i)
	{
		//i��°�� ��ǲ���� �˾ƿ���
		CompileInfo->GetResourceBindingDesc(i, &ResDesc);

		//���̴� ���� i��° Input �̸�
		std::string Name = ResDesc.Name;

		//Input Ÿ��
		D3D_SHADER_INPUT_TYPE Type = ResDesc.Type;

		switch (Type)
		{
			//��������� ��� GameEngineConstantBuffer���ҽ� �����
		case D3D_SIT_CBUFFER:
		{
			//�ش� ��������� ���� ����
			ID3D11ShaderReflectionConstantBuffer* CBufferPtr = CompileInfo->GetConstantBufferByName(ResDesc.Name);
			D3D11_SHADER_BUFFER_DESC BufferDesc;
			CBufferPtr->GetDesc(&BufferDesc);

			//������۸� ����ų� ��Ȱ���Ѵ�
			std::string UpperName = GameEngineString::ToUpper(ResDesc.Name);
			std::shared_ptr<GameEngineConstantBuffer> Buffer 
				= GameEngineConstantBuffer::CreateAndFind(BufferDesc.Size, UpperName, BufferDesc);


			GameEngineConstantBufferSetter Setter;
			Setter.ParentShader = this;
			Setter.Name = UpperName;
			//���̴� ������ GPU�������� ��ȣ
			Setter.BindPoint = ResDesc.BindPoint;
			Setter.Res = Buffer;

			//������� ���� �ȿ� ������� ���͸� �����Ѵ�
			ResHelper.CreateConstantBufferSetter(Setter);
			break;
		}
		case D3D_SIT_TEXTURE:
		{
			// �� ���ҽ��� �ؽ�ó �Դϴ�.
			break;
		}
		case D3D_SIT_SAMPLER:
		{
			// �� ���ҽ��� ���÷� �Դϴ�.
			break;
		}
		default:
			break;
		}
	}

}
