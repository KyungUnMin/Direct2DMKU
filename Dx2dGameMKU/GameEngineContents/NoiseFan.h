#pragma once
#include "FieldEnemyBase.h"

class NoiseFan : public FieldEnemyBase
{
public:
	NoiseFan();
	~NoiseFan() override;

	NoiseFan(const NoiseFan& _Other) = delete;
	NoiseFan(NoiseFan&& _Other) noexcept = delete;
	NoiseFan& operator=(const NoiseFan& _Other) = delete;
	NoiseFan& operator=(const NoiseFan&& _Other) noexcept = delete;

	inline bool OnDamage_Face(int _Damage) override
	{
		ChangeFlyState();
		return true;
	}
	inline bool OnDamage_Stomach(int _Damage) override
	{
		ChangeFlyState();
		return true;
	}
	inline bool OnDamage_Jaw(int _Damage) override
	{
		ChangeFlyState();
		return true;
	}
	inline bool OnDamage_BlowBack(int _Damage) override 
	{
		ChangeFlyState();
		return true;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	static const std::string_view Boy_FileName;
	static const std::string_view Girl_FileName;
	static const std::string_view BoyHurt_FileName;
	static const std::string_view GirlHurt_FileName;
	static const std::vector<std::string_view> EnumToString;

	enum class State
	{
		Climb,
		Trace,
		FlyAway,
		Fall,
	};

	State CurState = State::Climb;
	bool IsZenderGirl = true;
	std::shared_ptr<class GameEngineSpriteRenderer> HurtRender = nullptr;


	void ImageLoad();
	void CreateAnimation();
	void ChangeState(State _Next);
	void ChangeFlyState();

	void Update_Climb(float _DeltaTime);
	void Update_Trace(float _DeltaTime);
	void Update_FlyAway(float _DeltaTime);
	void Update_Fall(float _DeltaTime);

	//================FSM===================

	float4 TraceVec = float4::Zero;
	float LastAttackTime = 0.f;
};

