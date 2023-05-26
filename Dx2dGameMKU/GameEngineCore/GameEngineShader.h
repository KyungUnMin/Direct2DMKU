#pragma once
#include "GameEngineEnum.h"
#include "GameEngineShaderResHelper.h"

class GameEngineShader
{
public:
	GameEngineShader();
	~GameEngineShader();

	GameEngineShader(const GameEngineShader& _Other) = delete;
	GameEngineShader(GameEngineShader&& _Other) noexcept = delete;
	GameEngineShader& operator=(const GameEngineShader& _Other) = delete;
	GameEngineShader& operator=(const GameEngineShader&& _Other) noexcept = delete;

	//인자 : 어떤 쉐이더 타입인지(버텍스 쉐이더면 vs, 픽셀 쉐이더면 ps), 5.0버전
	void CreateVersion(const std::string_view& _ShaderType, UINT _VersionHigh = 5, UINT _VersionLow = 0);

	//쉐이더 파일의 main함수명 기입
	inline void SetEntryPoint(const std::string_view& _EntryPoint)
	{
		EntryPoint = _EntryPoint;
	}

	inline const GameEngineShaderResHelper& GetShaderResHelper() const
	{
		return ResHelper;
	}

	inline ShaderType GetType() const
	{
		return Type;
	}

	static void AutoCompile(GameEngineFile& _File);

protected:
	ShaderType Type = ShaderType::None;

	//쉐이더 코드를 2진 데이터로 변형하여
	//그래픽 카드에 전송했을때 받는 핸들러
	ID3DBlob* BinaryCode = nullptr;
	std::string Version = "";

	//쉐이더 파일의 main함수명
	std::string EntryPoint = "";


	//쉐이더 파일을 컴파일 하고 난 후 리플렉션을 통해 얻은 정보로 리소스를 생성/설정하기
	void ShaderResCheck();

private:
	/*
		GameEngineShader에서의 역할
			쉐이더 파일이 어떤 리소스 종류(상수버퍼나 텍스처들)들을 사용하는지 기록
		GameEngineRender에서의 역할
			렌더링 파이프라인이 세팅될때 GameEngineShader들에 있는 정보를 Copy함
	*/
	GameEngineShaderResHelper ResHelper;
};

