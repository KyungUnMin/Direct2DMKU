#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GameEngineUIRenderer;

class ScreenChainLock : public GameEngineActor
{
public:
	ScreenChainLock();
	~ScreenChainLock();

	ScreenChainLock(const ScreenChainLock& _Other) = delete;
	ScreenChainLock(ScreenChainLock&& _Other) noexcept = delete;
	ScreenChainLock& operator=(const ScreenChainLock& _Other) = delete;
	ScreenChainLock& operator=(const ScreenChainLock&& _Other) noexcept = delete;

	//충돌체의 위치와 크기를 설정합니다.
	void SetTriggerColArea(const float4& _Pos, const float4& _Scale);

	//플레이어와 충돌시 해야할 일을 설정합니다
	inline void SetTriggerCollBack(std::function<void()> _TriggerCallback)
	{
		TriggerCallback = _TriggerCallback;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	static const std::string_view SpriteHeadName;
	static const std::vector<std::string_view> ChainPoses;
	static const std::vector<std::string_view> ChainStates;
	static const std::vector<std::string_view> LockStates;
	static std::string TempSpriteName;	
	static const std::vector<std::string_view> LockSFX;
	
	enum class ChainStateType
	{
		Launch,
		Leave,
		Wobble,
	};

	enum class LockStateType
	{
		Appear,
		Damage1,
		Damage2,
		Damage3,
		Disappear
	};

	enum class State
	{
		Wait,
		Lock,
		Destroy,
	};

	std::vector<std::shared_ptr<GameEngineUIRenderer>> ChainRenders;
	std::shared_ptr<GameEngineUIRenderer> LockRender = nullptr;
	std::shared_ptr<class GameEngineCollision> Collider = nullptr;
	State CurState = State::Wait;
	LockStateType LockState = LockStateType::Appear;

	float4 PrevPlayerPos = float4::Zero;
	GameEngineTransform* PlayerTrans = nullptr;
	std::function<void()> TriggerCallback = nullptr;


	void LoadImageRes();
	void CreateChainRender();
	void CreateChainAnimation(size_t _PosIdx, size_t _StateIdx);
	void CreateLockRender();
	void CreateCollider();

	void Update_Wait();
	void Update_Lock();
	void Update_Destroy();

	void HitLock();
	void LockBreak();
};

