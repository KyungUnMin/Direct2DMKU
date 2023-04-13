#pragma once
#include "GameEngineResource.h"
#include "GameEngineShader.h"

class GameEnginePixelShader : public GameEngineResource<GameEnginePixelShader>, public GameEngineShader
{
public:
	GameEnginePixelShader();
	~GameEnginePixelShader() override;

	GameEnginePixelShader(const GameEnginePixelShader& _Other) = delete;
	GameEnginePixelShader(GameEnginePixelShader&& _Other) noexcept = delete;
	GameEnginePixelShader& operator=(const GameEnginePixelShader& _Other) = delete;
	GameEnginePixelShader& operator=(const GameEnginePixelShader&& _Other) noexcept = delete;


	//쉐이더 파일의 경로와 쉐이더 파일의 메인함수, 버전들을 입력받아서 쉐이더 파일을 컴파일하고 핸들러를 받아온다(이름은 자동으로 파일 말단 주소명으로 지정)
	static std::shared_ptr<GameEnginePixelShader> Load(const std::string_view& _Path, const std::string_view& _EntryPoint, UINT _VersionHigh = 5, UINT _VersionLow = 0)
	{
		GameEnginePath Path = GameEnginePath(std::string(_Path.data()));
		//이 함수와 똑같지만 이름만 파일의 말단 경로로 지정, 
		return Load(_Path, Path.GetFileName(), _EntryPoint, _VersionHigh, _VersionLow);
	}

	//쉐이더 파일의 경로와 이 객체의 이름, 쉐이더 파일의 메인함수, 버전들을 입력받아서 쉐이더 파일을 컴파일하고 핸들러를 받아온다
	static std::shared_ptr<GameEnginePixelShader> Load(const std::string_view& _Path, const std::string_view& _Name, const std::string_view& _EntryPoint, UINT _VersionHigh = 5, UINT _VersionLow = 0)
	{
		std::shared_ptr<GameEnginePixelShader> Res = GameEnginePixelShader::Create(_Name);
		Res->ShaderLoad(_Path, _EntryPoint, _VersionHigh, _VersionLow);
		return Res;
	}

	//픽셀 쉐이더 세팅
	void Setting() override;

protected:

private:
	//GPU에 전송한 쉐이더 바이너리 코드의 핸들러
	ID3D11PixelShader* ShaderPtr = nullptr;

	//쉐이더파일 컴파일 후 GPU에 전송하기
	void ShaderLoad(const std::string_view& _Path, const std::string_view& _EntryPoint, UINT _VersionHigh = 5, UINT _VersionLow = 0);
};

