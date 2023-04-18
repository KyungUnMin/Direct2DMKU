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

public:
	virtual void Setting() = 0;
};

//-------------------------Setter-----------------------


class GameEngineConstantBufferSetter : public GameEngineShaderResources
{
public:
	std::shared_ptr<GameEngineConstantBuffer> Res;
	const void* CPUData = nullptr;
	size_t CPUDataSize = 0;

	//이 상수버퍼의 값을 재갱신하고 해당 상수버퍼가 쉐이더 파일 어떤 슬롯인지 설정한다
	void Setting() override;
};


class GameEngineTextureSetter : public GameEngineShaderResources
{
public:
	std::shared_ptr<GameEngineTexture> Res;


	void Setting() override{}
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
	//멀티맵으로 만들었다
	std::multimap<std::string, GameEngineConstantBufferSetter> ConstantBuffer;

public:
	//자료구조에 저장
	void CreateConstantBufferSetter(const GameEngineConstantBufferSetter& _Buffer)
	{
		ConstantBuffer.insert(std::make_pair(_Buffer.Name, _Buffer));
	}



	//멀티맵안에 인자로 받은 이름의 상수버퍼가 있는지 확인하는 함수
	bool IsConstantBufferSetter(const std::string_view& _Name)
	{
		std::string UpperName = GameEngineString::ToUpper(_Name);
		std::multimap<std::string, GameEngineConstantBufferSetter>::iterator FindIter = ConstantBuffer.find(UpperName);

		if (ConstantBuffer.end() == FindIter)
			return false;

		return true;
	}


	template <typename DataType>
	void SetConstantBufferLink(const std::string_view& _Name, const DataType& _Data)
	{
		SetConstantBufferLink(_Name, reinterpret_cast<const void*>(&_Data), sizeof(DataType));
	}

	//CPU의 값과 GPU의 상수버퍼 값을 연동시키는 함수
	void SetConstantBufferLink(const std::string_view& _Name, const void* _Data, size_t _Size);


	/*같은 랜파를 쓸 때 랜더러마다 다른 상수나 텍스처를 넣어주기 위함
		그래서 Copy를 통해 쉐이더 리소스 헬퍼에 있는 세터들을 복시 한다
		쉐이더 안에 있는 리소스헬퍼는 리플렉션할 때 어떤 버퍼들을 사용했는지 조사만 하기 위함*/
	void Copy(const GameEngineShaderResHelper& _ResHelper);


	//자신 안에 있는 상수버퍼세터들의 Setting함수들을 호출시켜준다
	void Setting();
};