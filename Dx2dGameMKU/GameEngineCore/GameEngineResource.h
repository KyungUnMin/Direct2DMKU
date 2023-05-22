#pragma once
#include <map>
#include <list>
#include <memory>
#include <GameEngineBase/GameEngineString.h>
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineCore/GameEngineNameObject.h>
#include "GameEngineDevice.h"

//��� ���ҽ����� �θ� �ȴ�
//�ڽĵ鿡�� ����� ����
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

	//�������� ���ҽ��� ���� ����� �Լ�
	static void ResourcesClear()
	{
		for (std::shared_ptr<ResourceType> Type : UnNamedRes)
		{
			Type->IsUnLoad = true;
		}

		for (std::pair<std::string, std::shared_ptr<ResourceType>> Type : NamedResources)
		{
			Type.second->IsUnLoad = true;
		}

		NamedResources.clear();
		UnNamedRes.clear();
	}



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
			MsgAssert("�̹� �����ϴ� �̸��� ���ҽ��� �� ������� �߽��ϴ�");
			return nullptr;
		}

		std::shared_ptr<ResourceType> NewRes = std::make_shared<ResourceType>();
		NewRes->SetName(UpperName);

		NamedResources.insert(std::map<std::string, std::shared_ptr<ResourceType>>::value_type(UpperName, NewRes));
		return NewRes;
	}

private:
	std::string Path;
	//std::string Name;
	bool IsUnLoad = false;

	static std::map<std::string, std::shared_ptr<ResourceType>> NamedResources;
	static std::list<std::shared_ptr<ResourceType>> UnNamedRes;
};



template <typename ResourceType>
std::map<std::string, std::shared_ptr<ResourceType>> GameEngineResource<ResourceType>::NamedResources;

template <typename ResourceType>
std::list<std::shared_ptr<ResourceType>> GameEngineResource<ResourceType>::UnNamedRes;
