#pragma once
#include "GameEngineConstantBuffer.h"
#include "GameEngineTexture.h"


/*
	쉐이더 파일의 재료가 되는 것들은
	Setter클래스가 가르키고 있게 되는데,
	그 Setter클래스들은 모두 이 클래스를 상속받는다
*/
class GameEngineShaderResources
{
public:
	std::string Name;
	class GameEngineShader* ParentShader = nullptr;
	//b0, t0같은 몇번째 슬롯에 세팅되어야 하는지에 대한 정보
	int BindPoint = -1;
};

//-------------------------Setter-----------------------


class GameEngineTextureSetter : public GameEngineShaderResources
{
public:
	std::shared_ptr<GameEngineTexture> Res;
};


class GameEngineConstantBufferSetter : public GameEngineShaderResources
{
public:
	std::shared_ptr<GameEngineConstantBuffer> Res;
};


//-------------------------Helper-----------------------

class GameEngineShaderResHelper
{
private:
	// GameEngineDevice::GetContext()->VSSetConstantBuffers();
	// GameEngineDevice::GetContext()->PSSetConstantBuffers();
	//위와 같이 상수버퍼를 넣을때 버텍스쉐이더와 픽셀쉐이더가 분리되어 있다.
	// 그에비해 쉐이더 파일에서는 버텍스쉐이더와 픽셀쉐이더의 Input 상수값이 겹칠수가 있다
	//때문에 버텍스 쉐이더와 픽셀 쉐이더가 동일한 이름을 가진 경우를 고려해서
	//멀티맵으로 만들었다(일단 조금더 완성되어야 알 수 있을것 같다)
	std::multimap<std::string, GameEngineConstantBufferSetter> ConstantBuffer;

public:
	//자료구조에 저장
	void CreateConstantBufferSetter(const GameEngineConstantBufferSetter& _Buffer)
	{
		ConstantBuffer.insert(std::make_pair(_Buffer.Name, _Buffer));
	}

	//복사? 뭐에 쓰는 거지?
	void Copy(const GameEngineShaderResHelper& _ResHelper);
};