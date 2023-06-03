#pragma once
#include "GameEngineResource.h"


//쉐이더 파일의 시맨틱 문법과 실제 넣어주는 자료형을 대응시키기 위한 랜파 과정(인풋 어셈블러1)
class GameEngineInputLayOut : public GameEngineResource<GameEngineInputLayOut>
{
public:
	GameEngineInputLayOut();
	~GameEngineInputLayOut() override;

	GameEngineInputLayOut(const GameEngineInputLayOut& _Other) = delete;
	GameEngineInputLayOut(GameEngineInputLayOut&& _Other) noexcept = delete;
	GameEngineInputLayOut& operator=(const GameEngineInputLayOut& _Other) = delete;
	GameEngineInputLayOut& operator=(const GameEngineInputLayOut&& _Other) noexcept = delete;

	void Release();

	//레이아웃을 만들기 위해서는 버텍스 버퍼에 있는 레이아웃 정보와 버텍스 쉐이더의 바이너리 코드를 알아야 한다
	void ResCreate(std::shared_ptr<class GameEngineVertexBuffer> _Info, std::shared_ptr<class GameEngineVertexShader> _Shader);

	//GPU에 레이아웃 정보를 세팅
	void Setting() override;

	inline bool IsCreate() const
	{
		return (nullptr != InputLayOut);
	}

protected:

private:
	ID3D11InputLayout* InputLayOut = nullptr;
};

