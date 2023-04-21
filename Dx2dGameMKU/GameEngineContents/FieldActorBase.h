#pragma once
#include <GameEngineCore/GameEngineActor.h>


class FieldActorBase : public GameEngineActor
{
public:
	FieldActorBase();
	virtual ~FieldActorBase() = 0;

	FieldActorBase(const FieldActorBase& _Other) = delete;
	FieldActorBase(FieldActorBase&& _Other) noexcept = delete;
	FieldActorBase& operator=(const FieldActorBase& _Other) = delete;
	FieldActorBase& operator=(const FieldActorBase&& _Other) noexcept = delete;

	inline float GetHeight() const
	{
		return Height;
	}

	inline void SetHeight(float _Value)
	{
		Height = _Value;
		if (Height < 0.f)
		{
			Height = 0.f;
		}
	}

	inline void AddHeight(float _AddValue)
	{
		Height += _AddValue;
		if (Height < 0.f)
		{
			Height = 0.f;
		}
	}

	inline bool IsZeroHeight() const
	{
		return (0.f == Height);
	}


protected:
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	float Height = 0.f;

};

