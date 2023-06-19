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

	inline void Init(float _MoveLength)
	{
		MoveLength = _MoveLength;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:

	enum class State
	{

	};

	float MoveLength = 0.f;
};

