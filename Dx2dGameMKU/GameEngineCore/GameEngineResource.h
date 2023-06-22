#pragma once
#include <map>
#include <list>
#include <mutex>
#include <memory>
#include <GameEngineBase/GameEngineString.h>
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineCore/GameEngineNameObject.h>
#include "GameEngineDevice.h"

//모든 리소스들의 부모가 된다
//자식들에게 기능을 제공
template <typename ResourceType>
class GameEngineResource : public GameEngineNameObject
{
public:
	friend class GameEngineCore;

	GameEngineResource(){}
	virtual ~GameEngineResource() = 0{}

	GameEngineResource(const GameEngineResource& _Other) = delete;
	GameEngineResource(GameEngineResource&& _Other) noexcept = delete;
	GameEngineResource& operator=(const GameEngineResource& _Other) = delete;
	GameEngineResource& operator=(const GameEngineResource&& _Other) noexcept = delete;

	inline std::string_view GetPath() const
	{
		return Path.c_str();
	}


	inline void SetPath(const std::string_view& _Value)
	{
		Path = _Value;
	}

	static std::shared_ptr<ResourceType> Find(const std::string_view& _Name)
	{
		std::string UpperName = GameEngineString::ToUpper(_Name);

		//Find하는 사이에 다른 스레드에서 NamedResources에 노드가 추가될 수도 있기 때문에 Lock처리한다
		NameLock.lock();
		if (NamedResources.end() == NamedResources.find(UpperName))
		{
			NameLock.unlock();
			return nullptr;
		}
		NameLock.unlock();

		return NamedResources[UpperName];
	}

	virtual void Setting(){}

	
	static void ResourcesClear()
	{
		NamedResources.clear();
		UnNamedRes.clear();
	}



protected:
	static std::shared_ptr<ResourceType> CreateUnNamed()
	{
		std::shared_ptr<ResourceType> NewRes = std::make_shared<ResourceType>();

		//공유메모리 수정 문제 보호
		UnNamedLock.lock();
		UnNamedRes.push_back(NewRes);
		UnNamedLock.unlock();

		return NewRes;
	}

	static std::shared_ptr<ResourceType> Create(const std::string_view& _Name)
	{
		std::string UpperName = GameEngineString::ToUpper(_Name);


		//Find하는 사이에 다른 스레드에서 NamedResources에 노드가 추가될 수도 있기 때문에 Lock처리한다
		NameLock.lock();
		if (NamedResources.end() != NamedResources.find(UpperName))
		{
			MsgAssert("이미 존재하는 이름의 리소스를 또 만들려고 했습니다");
			NameLock.unlock();
			return nullptr;
		}
		NameLock.unlock();


		std::shared_ptr<ResourceType> NewRes = std::make_shared<ResourceType>();
		NewRes->SetName(UpperName);

		//공유메모리 수정 문제 보호
		NameLock.lock();
		NamedResources.insert(std::map<std::string, std::shared_ptr<ResourceType>>::value_type(UpperName, NewRes));
		NameLock.unlock();

		return NewRes;
	}

private:
	std::string Path;

	static std::map<std::string, std::shared_ptr<ResourceType>> NamedResources;
	static std::mutex NameLock;

	static std::list<std::shared_ptr<ResourceType>> UnNamedRes;
	static std::mutex UnNamedLock;
};



template <typename ResourceType>
std::map<std::string, std::shared_ptr<ResourceType>> GameEngineResource<ResourceType>::NamedResources;

template<typename ResourcesType>
std::mutex GameEngineResource<ResourcesType>::NameLock;



template <typename ResourceType>
std::list<std::shared_ptr<ResourceType>> GameEngineResource<ResourceType>::UnNamedRes;

template<typename ResourcesType>
std::mutex GameEngineResource<ResourcesType>::UnNamedLock;
