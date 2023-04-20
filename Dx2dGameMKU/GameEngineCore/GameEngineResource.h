#pragma once
#include <map>
#include <list>
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

	/*inline std::string_view GetName() const
	{
		return Name.c_str();
	}*/


	/*inline std::string GetNameToString() const
	{
		return Name;
	}*/

	inline void SetPath(const std::string_view& _Value)
	{
		Path = _Value;
	}

	/*inline void SetName(const std::string_view& _Value)
	{
		Name = _Value;
	}*/

	static std::shared_ptr<ResourceType> Find(const std::string_view& _Name)
	{
		std::string UpperName = GameEngineString::ToUpper(_Name);

		if (NamedResources.end() == NamedResources.find(UpperName))
		{
			return nullptr;
		}

		return NamedResources[UpperName];
	}

	virtual void Setting(){}

protected:
	static std::shared_ptr<ResourceType> CreateUnNamed()
	{
		std::shared_ptr<ResourceType> NewRes = std::make_shared<ResourceType>();
		UnNamedRes.push_back(NewRes);
		return NewRes;
	}

	static std::shared_ptr<ResourceType> Create(const std::string_view& _Name)
	{
		std::string UpperName = GameEngineString::ToUpper(_Name);

		if (NamedResources.end() != NamedResources.find(UpperName))
		{
			MsgAssert("이미 존재하는 이름의 리소스를 또 만들력 했습니다");
			return nullptr;
		}

		std::shared_ptr<ResourceType> NewRes = std::make_shared<ResourceType>();
		NewRes->SetName(UpperName);

		NamedResources.insert(std::map<std::string, std::shared_ptr<ResourceType>>::value_type(UpperName, NewRes));
		return NewRes;
	}

	static void ResourcesClear()
	{
		NamedResources.clear();
		UnNamedRes.clear();
	}

private:
	std::string Path;
	//std::string Name;

	static std::map<std::string, std::shared_ptr<ResourceType>> NamedResources;
	static std::list<std::shared_ptr<ResourceType>> UnNamedRes;
};



template <typename ResourceType>
std::map<std::string, std::shared_ptr<ResourceType>> GameEngineResource<ResourceType>::NamedResources;

template <typename ResourceType>
std::list<std::shared_ptr<ResourceType>> GameEngineResource<ResourceType>::UnNamedRes;
