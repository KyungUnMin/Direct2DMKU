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

protected:

private:
	//쉐이더 코드를 2진 데이터로 변형하여
	//그래픽 카드에 전송했을때 받는 핸들러
	ID3DBlob* BinaryCode = nullptr;
	std::string Version;
};

