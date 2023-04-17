#pragma once
#include "GameEngineResource.h"
#include "GameEngineDirectBuffer.h"

/*
	쉐이더 파일에 상수값을 입력할 때 사용되는
	상수버퍼를 관리하는 클래스이다.
	상수버퍼가 쉐이더 파일마다 존재하면
	메모리 낭비이기 때문에
	같은 크기의 상수버퍼들을 재활용하게 된다
*/

class GameEngineConstantBuffer : public GameEngineResource<GameEngineConstantBuffer>, public GameEngineDirectBuffer
{
public:
	GameEngineConstantBuffer();
	~GameEngineConstantBuffer() override;

	GameEngineConstantBuffer(const GameEngineConstantBuffer& _Other) = delete;
	GameEngineConstantBuffer(GameEngineConstantBuffer&& _Other) noexcept = delete;
	GameEngineConstantBuffer& operator=(const GameEngineConstantBuffer& _Other) = delete;
	GameEngineConstantBuffer& operator=(const GameEngineConstantBuffer&& _Other) noexcept = delete;

	static std::shared_ptr<GameEngineConstantBuffer> CreateAndFind(
		int _Byte, const std::string_view& _Name, 
		const D3D11_SHADER_BUFFER_DESC& _BufferDesc)
	{
		//해당 크기의 상수버퍼가 존재하지 않는다면 무조건 만든다
		if (ConstantBufferRes.end() == ConstantBufferRes.find(_Byte))
		{
			ConstantBufferRes[_Byte];
		}

		std::string UpperName = GameEngineString::ToUpper(_Name.data());

		//이름으로 찾았을때 있다면 그 버퍼를 재활용한다.
		if (ConstantBufferRes[_Byte].end() != ConstantBufferRes[_Byte].find(UpperName))
		{
			return ConstantBufferRes[_Byte][UpperName];
		}

		//버퍼를 새로 만들고 초기 세팅해준다
		std::shared_ptr<GameEngineConstantBuffer> Buffer = CreateUnNamed();
		ConstantBufferRes[_Byte][UpperName] = Buffer;
		Buffer->ResCreate(_BufferDesc);

		return Buffer;
	}

	//static 멤버변수의 map 정리
	static void ResourcesClear();

protected:
	//새로 만들어진 버퍼를 초기세팅한다(크기, 상수버퍼 표시, GPU 수정권한)
	void ResCreate(const D3D11_SHADER_BUFFER_DESC& _BufferDesc);

private:
	//<상수 버퍼 크기, <이름, 포인터>>
	static std::map<int, std::map<std::string, std::shared_ptr<GameEngineConstantBuffer>>> ConstantBufferRes;
};

