#pragma once
#include <map>
#include <list>
#include <mutex>
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


	inline void SetPath(const std::string_view& _Value)
	{
		Path = _Value;
	}

	static std::shared_ptr<ResourceType> Find(const std::string_view& _Name)
	{
		std::string UpperName = GameEngineString::ToUpper(_Name);

		//Find�ϴ� ���̿� �ٸ� �����忡�� NamedResources�� ��尡 �߰��� ���� �ֱ� ������ Lockó���Ѵ�
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

		//�����޸� ���� ���� ��ȣ
		UnNamedLock.lock();
		UnNamedRes.push_back(NewRes);
		UnNamedLock.unlock();

		return NewRes;
	}

	static std::shared_ptr<ResourceType> Create(const std::string_view& _Name)
	{
		std::string UpperName = GameEngineString::ToUpper(_Name);


		//Find�ϴ� ���̿� �ٸ� �����忡�� NamedResources�� ��尡 �߰��� ���� �ֱ� ������ Lockó���Ѵ�
		NameLock.lock();
		if (NamedResources.end() != NamedResources.find(UpperName))
		{
			MsgAssert("�̹� �����ϴ� �̸��� ���ҽ��� �� ������� �߽��ϴ�");
			NameLock.unlock();
			return nullptr;
		}
		NameLock.unlock();


		std::shared_ptr<ResourceType> NewRes = std::make_shared<ResourceType>();
		NewRes->SetName(UpperName);

		//�����޸� ���� ���� ��ȣ
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
