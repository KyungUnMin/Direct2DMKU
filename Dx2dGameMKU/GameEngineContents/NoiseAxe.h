#pragma once
#include "FieldActorBase.h"

class NoiseAxe : public FieldActorBase
{
public:
	NoiseAxe();
	~NoiseAxe() override;

	NoiseAxe(const NoiseAxe& _Other) = delete;
	NoiseAxe(NoiseAxe&& _Other) noexcept = delete;
	NoiseAxe& operator=(const NoiseAxe& _Other) = delete;
	NoiseAxe& operator=(const NoiseAxe&& _Other) noexcept = delete;

	inline void Init(
		const float4& _StartPos, 
		const float4& _DestPos, 
		float _MoveDuration,
		float _StayDuration)
	{
		StartPos = _StartPos;
		DestPos = _DestPos;
		MoveDuration = _MoveDuration;
		StayDuration = _StayDuration;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	static const std::string_view AniFileName;
	static const int Damage;

	enum class State
	{
		Launch,
		Stay,
		ComeBack
	};

	State CurState = State::Launch;

	float4 StartPos = float4::Zero;
	float4 DestPos = float4::Zero;
	float MoveDuration = 0.f;
	float StayDuration = 0.f;
	float AttackTimer = 10.f;

	std::shared_ptr<class BackGround> BGPtr = nullptr;


	void ImageLoad();
	void SettingRender();

	void Update_Launch(float _DeltaTime);
	void Update_Stay(float _DeltaTime);
	void Update_ComeBack(float _DeltaTime);
};

