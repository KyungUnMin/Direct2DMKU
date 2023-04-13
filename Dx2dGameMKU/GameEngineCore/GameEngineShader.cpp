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
	// ¿¹½Ã : vs_5_0
	Version += _ShaderType;
	Version += "_";
	Version += std::to_string(_VersionHigh);
	Version += "_";
	Version += std::to_string(_VersionLow);
}
