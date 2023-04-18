#include "PrecompileHeader.h"
#include "GameEnginePixelShader.h"

GameEnginePixelShader::GameEnginePixelShader()
{
	Type = ShaderType::Pixel;
}

GameEnginePixelShader::~GameEnginePixelShader()
{
	if (nullptr != ShaderPtr)
	{
		ShaderPtr->Release();
		ShaderPtr = nullptr;
	}
}



void GameEnginePixelShader::ShaderLoad(
	const std::string_view& _Path, 
	const std::string_view& _EntryPoint, 
	UINT _VersionHigh, 
	UINT _VersionLow)
{
	//���̴� ������ ���̳ʸ� �ڵ带 �ε��ϱ� ���� ���� ���
	GameEngineShader::CreateVersion("ps", _VersionHigh, _VersionLow);
	//���̴����� ������ ����
	GameEngineShader::SetEntryPoint(_EntryPoint);


	unsigned int Flag = 0;
#ifdef _DEBUG
	Flag = D3D10_SHADER_DEBUG;
#endif

	//������ �� �� ������ ���߿� ��������� �� �� �� �ִ�
	Flag |= D3DCOMPILE_PACK_MATRIX_ROW_MAJOR;


	//���̴� ���� �������� ���������� ������ �˱����� ���� �ڵ鷯
	ID3DBlob* Error = nullptr;


	//��� MBCS����  WBCS�� ��ȯ
	std::wstring UniCodePath = GameEngineString::AnsiToUniCode(_Path);


	//���̴� ���� ������ ��Ű��(�����ϵ� ����� �ڵ鷯�� BinaryCode�� �޾ƿ�)
	HRESULT Result = D3DCompileFromFile
	(
		UniCodePath.c_str(),										//WBCS���
		nullptr,															//�ܺο��� #define �� ����
		D3D_COMPILE_STANDARD_FILE_INCLUDE,	//���̴� ���� ���ο� �ִ� #include ����
		EntryPoint.c_str(),											//���̴� ���� ������ �̸�
		Version.c_str(),												//���� �̸�
		Flag,																	//
		0,																		//�˾Ƽ� ����
		&BinaryCode,													//�ڵ鷯 ��ȯ
		&Error																//���������� ���� ���� ��ȯ
	);

	//���̴� ���� �������� ���������� ������ ȭ�鿡 ����ֱ�
	if (S_OK != Result)
	{
		std::string ErrorString = reinterpret_cast<char*>(Error->GetBufferPointer());
		MsgAssert(ErrorString);
		return;
	}

	//GPU���� �����ϵ� ���̴� ���̳ʸ� �ڵ带 ������ ShaderPtr�� �ڵ鷯 �޾ƿ���
	Result = GameEngineDevice::GetDevice()->CreatePixelShader
	(
		BinaryCode->GetBufferPointer(),
		BinaryCode->GetBufferSize(),
		nullptr,
		&ShaderPtr
	);

	//������ ���
	if (S_OK != Result)
	{
		MsgAssert("���ؽ� ���̴� �ڵ� ������ �����߽��ϴ�");
		return;
	}

	GameEngineShader::ShaderResCheck();
}


void GameEnginePixelShader::Setting()
{
	if (nullptr == ShaderPtr)
	{
		MsgAssert("�ȼ� ���̴��� �������� �ʽ��ϴ� ���ÿ� �����߽��ϴ�.");
	}

	GameEngineDevice::GetContext()->PSSetShader(ShaderPtr, nullptr, 0);
}