#include "PrecompileHeader.h"
#include "GameEngineVertexShader.h"

GameEngineVertexShader::GameEngineVertexShader()
{
	Type = ShaderType::Vertex;
}

GameEngineVertexShader::~GameEngineVertexShader()
{
	if (nullptr != ShaderPtr)
	{
		ShaderPtr->Release();
		ShaderPtr = nullptr;
	}
}

void GameEngineVertexShader::ShaderLoad(
	const std::string_view& _Path, 
	const std::string_view& _EntryPoint, 
	UINT _VersionHigh, 
	UINT _VersionLow)
{
	//���̴� ������ ���̳ʸ� �ڵ带 �ε��ϱ� ���� ���� ���
	GameEngineShader::CreateVersion("vs", _VersionHigh, _VersionLow);
	//���̴����� ������ ����
	GameEngineShader::SetEntryPoint(_EntryPoint);


	unsigned int Flag = 0;
#ifdef _DEBUG
	Flag = D3D10_SHADER_DEBUG;
#endif

	/*
		���̴� ���� �⺻������ ���ʺ��� ���η� ����
		�׷��� ��ġ��� ó�� ����
		(���ʺ��� ����ó�� �Ǽ� �׷���?)
		
		������ �Ʒ� �ɼ� �� �־��־�� �Ѵ�
	*/
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
	Result = GameEngineDevice::GetDevice()->CreateVertexShader
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

	//���̴� �������� �����ٸ� ���÷����� �̿��� ���̴��� �����ؼ�
	//�ʿ��� ���ҽ�(�������, �ؽ�ó ���)���� ���� �Ǵ� ��Ȱ���Ѵ�
	GameEngineShader::ShaderResCheck();
}

void GameEngineVertexShader::Setting()
{
	if (nullptr == ShaderPtr)
	{
		MsgAssert("���ؽ� ���̴��� �������� �ʽ��ϴ� ���ÿ� �����߽��ϴ�.");
	}

	//���ؽ� ���̴� ����
	GameEngineDevice::GetContext()->VSSetShader(ShaderPtr, nullptr, 0);
}


