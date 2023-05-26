#include "PrecompileHeader.h"
#include "GameEngineShader.h"

#include "GameEngineVertexShader.h"
#include "GameEnginePixelShader.h"

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

		std::string UpperName = GameEngineString::ToUpper(ResDesc.Name);

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
			std::shared_ptr<GameEngineConstantBuffer> Res 
				= GameEngineConstantBuffer::CreateAndFind(BufferDesc.Size, UpperName, BufferDesc);

			GameEngineConstantBufferSetter Setter;
			Setter.ParentShader = this;
			Setter.Name = UpperName;
			//쉐이더 파일의 GPU레지스터 번호
			Setter.BindPoint = ResDesc.BindPoint;
			Setter.Res = Res;

			//멤버변수 헬퍼 안에 상수버퍼 세터를 저장한다
			ResHelper.CreateConstantBufferSetter(Setter);
			break;
		}
		case D3D_SIT_TEXTURE:
		{
			//이후에 별도로 텍스처를 설정해주지 않으면 이 텍스처로 지정된다
			std::shared_ptr<GameEngineTexture> Res = GameEngineTexture::Find("EngineBaseTex.png");

			if (nullptr == Res)
			{
				MsgAssert("다음의 샘플러가 존재하지 않아서 쉐이더에 세팅해줄 수 가 없습니다 " + UpperName);
				return;
			}

			GameEngineTextureSetter Setter;
			Setter.ParentShader = this;
			Setter.Name = UpperName;
			//쉐이더 파일의 GPU레지스터 번호
			Setter.BindPoint = ResDesc.BindPoint;
			Setter.Res = Res;

			ResHelper.CreateTextureSetter(Setter);
			break;
		}
		case D3D_SIT_SAMPLER:
		{
			//엔진에서 지원하는 기본 샘플러
			std::shared_ptr<GameEngineSampler> Res = GameEngineSampler::Find(UpperName);

			GameEngineSamplerSetter Setter;
			Setter.ParentShader = this;
			Setter.Name = UpperName;
			//쉐이더 파일의 GPU레지스터 번호
			Setter.BindPoint = ResDesc.BindPoint;
			Setter.Res = Res;

			ResHelper.CreateSamplerSetter(Setter);
			break;
		}
		default:
			break;
		}
	}

}


void GameEngineShader::AutoCompile(GameEngineFile& _File)
{
	std::string ShaderCode = _File.GetString();

	//버텍스 쉐이더
	{
		size_t EntryIndex = ShaderCode.find("_VS(");
		// unsigned __int64 == max값이 std::string::npos
		if (EntryIndex != std::string::npos)
		{
			{
				size_t FirstIndex = ShaderCode.find_last_of(" ", EntryIndex);
				std::string EntryName = ShaderCode.substr(FirstIndex + 1, EntryIndex - FirstIndex - 1);
				EntryName += "_VS";
				GameEngineVertexShader::Load(_File.GetFullPath(), EntryName);
			}
		}
	}


	//픽셀 쉐이더
	{
		size_t EntryIndex = ShaderCode.find("_PS(");
		// unsigned __int64 == max값이 std::string::npos
		if (EntryIndex != std::string::npos)
		{
			{
				size_t FirstIndex = ShaderCode.find_last_of(" ", EntryIndex);
				std::string EntryName = ShaderCode.substr(FirstIndex + 1, EntryIndex - FirstIndex - 1);
				EntryName += "_PS";
				GameEnginePixelShader::Load(_File.GetFullPath(), EntryName);
			}
		}
	}

}