#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GameEngineSpriteRenderer;

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

	inline const std::pair<int, int>& GetGridPos() const
	{
		return GridPos;
	}

	inline std::shared_ptr<class GameEngineSpriteRenderer> GetRenderer() const
	{
		return RendererPtr;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	inline std::shared_ptr<class BackGround> GetBackGround() const
	{
		return BGPtr;
	}



private:
	float Height = 0.f;


	
	std::shared_ptr<class BackGround> BGPtr = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> GridPosRender_Debug = nullptr;
	std::pair<int, int> GridPos = { 0, 0 };

	std::shared_ptr<GameEngineSpriteRenderer> RendererPtr = nullptr;

	void CreateShadow();
	void CreateDebugGridPoint();
	void Update_GridDebug();
};

