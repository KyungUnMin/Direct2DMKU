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
	// 예시 : vs_5_0
	Version += _ShaderType;
	Version += "_";
	Version += std::to_string(_VersionHigh);
	Version += "_";
	Version += std::to_string(_VersionLow);
}


//쉐이더 파일을 컴파일 하고 난 후 리플렉션을 통해 정보를 얻어오는 함수
void GameEngineShader::ShaderResCheck()
{
	if (nullptr == BinaryCode)
	{
		MsgAssert("쉐이더 파일을 컴파일하지 않아서 리소스를 조사할 수 없습니다");
		return;
	}

	//리플렉션
	ID3D11ShaderReflection* CompileInfo = nullptr;
	if (S_OK != D3DReflect(BinaryCode->GetBufferPointer(), BinaryCode->GetBufferSize(), IID_ID3D11ShaderReflection,reinterpret_cast<void**>(&CompileInfo)))
	{
		MsgAssert("쉐이더 리플렉션에 실패하였습니다");
		return;
	}

	D3D11_SHADER_DESC Info;
	CompileInfo->GetDesc(&Info);

	//쉐이더 파일의 인풋 정보 알아오기
	D3D11_SHADER_INPUT_BIND_DESC ResDesc;
	// Info.BoundResources : 내가 사용한 상수버퍼, 텍스처, 샘플러등의 총합
	for (UINT i = 0; i < Info.BoundResources; ++i)
	{
		//i번째의 인풋정보 알아오기
		CompileInfo->GetResourceBindingDesc(i, &ResDesc);

		//쉐이더 파일 i번째 Input 이름
		std::string Name = ResDesc.Name;

		//Input 타입
		D3D_SHADER_INPUT_TYPE Type = ResDesc.Type;

		switch (Type)
		{
			//상수버퍼인 경우 GameEngineConstantBuffer리소스 만들기
		case D3D_SIT_CBUFFER:
		{
			//해당 상수버퍼의 정보 추출
			ID3D11ShaderReflectionConstantBuffer* CBufferPtr = CompileInfo->GetConstantBufferByName(ResDesc.Name);
			D3D11_SHADER_BUFFER_DESC BufferDesc;
			CBufferPtr->GetDesc(&BufferDesc);

			//상수버퍼를 만들거나 재활용한다
			std::string UpperName = GameEngineString::ToUpper(ResDesc.Name);
			std::shared_ptr<GameEngineConstantBuffer> Buffer 
				= GameEngineConstantBuffer::CreateAndFind(BufferDesc.Size, UpperName, BufferDesc);


			GameEngineConstantBufferSetter Setter;
			Setter.ParentShader = this;
			Setter.Name = UpperName;
			//쉐이더 파일의 GPU레지스터 번호
			Setter.BindPoint = ResDesc.BindPoint;
			Setter.Res = Buffer;

			//멤버변수 헬퍼 안에 상수버퍼 세터를 저장한다
			ResHelper.CreateConstantBufferSetter(Setter);
			break;
		}
		case D3D_SIT_TEXTURE:
		{
			// 이 리소스는 텍스처 입니다.
			break;
		}
		case D3D_SIT_SAMPLER:
		{
			// 이 리소스는 샘플러 입니다.
			break;
		}
		default:
			break;
		}
	}

}
