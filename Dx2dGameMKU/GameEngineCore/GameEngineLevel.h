#pragma once
#include <map>
#include <string_view>

#include <GameEngineBase/GameEngineTimeEvent.h>

#include "GameEngineObject.h"

class GameEngineActor;
class GameEngineCamera;
class GameEngineCollision;
class GameEngineRenderer;
class GameEngineRenderTarget;
enum class CameraType;

class GameEngineLevel : public GameEngineObject
{
	friend class GameEngineRenderer;
	friend class GameEngineTransform;
	friend class GameEngineCore;
	friend class GameEngineCollision;
	friend class GameEngineActor;
	friend class GameEngineTexture;

public:
	static void IsDebugSwitch()
	{
		IsDebugRender = !IsDebugRender;
	}


	GameEngineTimeEvent TimeEvent;

	GameEngineLevel();
	virtual ~GameEngineLevel();

	GameEngineLevel(const GameEngineLevel& _Other) = delete;
	GameEngineLevel(GameEngineLevel&& _Other) noexcept = delete;
	GameEngineLevel& operator=(const GameEngineLevel& _Other) = delete;
	GameEngineLevel& operator=(const GameEngineLevel&& _Other) noexcept = delete;

	template<typename ActorType>
	std::shared_ptr<ActorType> CreateActorToName(const std::string_view& _Name = "")
	{
		return CreateActor<ActorType>(0, _Name);
	}

	template<typename ActorType, typename EnumType>
	std::shared_ptr<ActorType> CreateActor(EnumType  _Order, const std::string_view& _Name = "")
	{
		return CreateActor<ActorType>(static_cast<int>(_Order), _Name);
	}

	template<typename ActorType>
	std::shared_ptr<ActorType> CreateActor(int _Order = 0, const std::string_view& _Name = "")
	{
		std::shared_ptr<GameEngineActor> NewActor = std::make_shared<ActorType>();

		//이름이 존재하지 않으면 클래스 명으로 이름 설정
		std::string Name = _Name.data();
		if ("" == Name)
		{
			const type_info& Info = typeid(ActorType);
			Name = Info.name();
			Name.replace(0, 6, "");
		}

		//Order 및 Parent 설정
		ActorInit(NewActor, _Order, this);
		
		return std::dynamic_pointer_cast<ActorType>(NewActor);
	}

	std::shared_ptr<GameEngineCamera> GetMainCamera()
	{
		return MainCamera;
	}

	std::shared_ptr<GameEngineLevel> GetSharedThis()
	{
		return DynamicThis<GameEngineLevel>();
	}

	std::shared_ptr<GameEngineCamera> GetCamera(int _CameraOrder);

	inline std::shared_ptr<GameEngineRenderTarget> GetLastTarget() const
	{
		return LastTarget;
	}


	std::shared_ptr<GameEngineCamera> CreateCamera(int _CameraNum, CameraType _ProjectionType);

protected:
	virtual void LevelChangeStart(){}
	virtual void LevelChangeEnd(){}
	
	virtual void Start() = 0;
	virtual void Update(float _DeltaTime){}
	virtual void Render(float _DeltaTime){}

private:
	static bool IsDebugRender;

	//모든 카메라의 이미지가 다 종합된 렌더타겟(도화지)
	std::shared_ptr<GameEngineRenderTarget> LastTarget;

	//<이름, 경로>, 텍스처를 로드할 때마다 기록한다
	std::map<std::string, std::string> TexturePath;
	//std::map<std::string, std::string> LoadEndPath;



	//이 레벨에 존재하는 카메라들
	std::map<int, std::shared_ptr<GameEngineCamera>> Cameras;

	//메인카메라(자주 사용되기 때문에 따로 포인터로 두었음)
	std::shared_ptr<GameEngineCamera> MainCamera;



	std::map<int, std::list<std::shared_ptr<GameEngineActor>>> Actors;

	std::map<int, std::list<std::shared_ptr<GameEngineCollision>>> Collisions;


	//_Index번째 카메라에 렌더러를 등록한다
	void PushCameraRenderer(std::shared_ptr<GameEngineRenderer> _Renderer, int _CameraOrder);

	//Collision의 SetOrder에서 호출됨
	void PushCollision(std::shared_ptr<GameEngineCollision> _Collision);

	//생성한 엑터 초기화
	void ActorInit(std::shared_ptr<GameEngineActor> _Actor, int _Order, GameEngineLevel* _Level);

	void ActorUpdate(float _DeltaTime);
	void ActorRender(float _DeltaTime);
	void ActorRelease();

	void ActorLevelChangeStart();
	void ActorLevelChangeEnd();

	/*void TextureUnLoad(GameEngineLevel* _NextLevel);
	void TextureReLoad(GameEngineLevel* _PrevLevel);*/
};

