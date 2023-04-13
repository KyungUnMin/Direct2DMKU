#pragma once


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

protected:
	//쉐이더 코드를 2진 데이터로 변형하여
	//그래픽 카드에 전송했을때 받는 핸들러
	ID3DBlob* BinaryCode = nullptr;
	std::string Version = "";

	//쉐이더 파일의 main함수명
	std::string EntryPoint = "";

private:
	
};

