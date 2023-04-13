#include "PrecompileHeader.h"
#include "GameEngineVertexShader.h"

GameEngineVertexShader::GameEngineVertexShader()
{

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
	//쉐이더 파일의 바이너리 코드를 로드하기 위한 버전 명시
	GameEngineShader::CreateVersion("vs", _VersionHigh, _VersionLow);
	//쉐이더파일 진입점 지정
	GameEngineShader::SetEntryPoint(_EntryPoint);


	unsigned int Flag = 0;
#ifdef _DEBUG
	Flag = D3D10_SHADER_DEBUG;
#endif

	//지금은 알 수 없지만 나중에 상수버퍼할 때 알 수 있다
	Flag |= D3DCOMPILE_PACK_MATRIX_ROW_MAJOR;


	//쉐이더 파일 컴파일이 에러났을때 원인을 알기위한 에러 핸들러
	ID3DBlob* Error = nullptr;


	//경로 MBCS에서  WBCS로 변환
	std::wstring UniCodePath = GameEngineString::AnsiToUniCode(_Path);


	//쉐이더 파일 컴파일 시키기(컴파일된 결과의 핸들러를 BinaryCode에 받아옴)
	HRESULT Result = D3DCompileFromFile
	(
		UniCodePath.c_str(),										//WBCS경로
		nullptr,															//외부에서 #define 할 내용
		D3D_COMPILE_STANDARD_FILE_INCLUDE,	//쉐이더 파일 내부에 있는 #include 해줘
		EntryPoint.c_str(),											//쉐이더 파일 진입점 이름
		Version.c_str(),												//버전 이름
		Flag,																	//
		0,																		//알아서 해줘
		&BinaryCode,													//핸들러 반환
		&Error																//에러났을때 에러 이유 반환
	);

	//쉐이더 파일 컴파일이 오류났을때 이유를 화면에 띄워주기
	if (S_OK != Result)
	{
		std::string ErrorString = reinterpret_cast<char*>(Error->GetBufferPointer());
		MsgAssert(ErrorString);
		return;
	}

	//GPU에게 컴파일된 쉐이더 바이너리 코드를 보내고 ShaderPtr에 핸들러 받아오기
	Result = GameEngineDevice::GetDevice()->CreateVertexShader
	(
		BinaryCode->GetBufferPointer(),
		BinaryCode->GetBufferSize(),	
		nullptr,										
		&ShaderPtr									
	);
	
	//실패한 경우
	if (S_OK != Result)
	{
		MsgAssert("버텍스 쉐이더 핸들 생성에 실패했습니다");
		return;
	}
}

void GameEngineVertexShader::Setting()
{
	if (nullptr == ShaderPtr)
	{
		MsgAssert("버텍스 쉐이더가 존재하지 않습니다 세팅에 실패했습니다.");
	}

	//버텍스 쉐이더 동작
	GameEngineDevice::GetContext()->VSSetShader(ShaderPtr, nullptr, 0);
}


