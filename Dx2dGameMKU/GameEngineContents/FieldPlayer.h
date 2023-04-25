#pragma once
#include "FieldActorBase.h"
#include "PlayerFSM.h"

class FieldPlayer : public FieldActorBase
{
public:
	static std::shared_ptr<FieldPlayer> GetPtr()
	{
		if (nullptr == GPtr)
		{
			return nullptr;
		}
		
		return GPtr->Shared_This_dynamic_pointer<FieldPlayer>();
	}


	FieldPlayer();
	~FieldPlayer() override;

	FieldPlayer(const FieldPlayer& _Other) = delete;
	FieldPlayer(FieldPlayer&& _Other) noexcept = delete;
	FieldPlayer& operator=(const FieldPlayer& _Other) = delete;
	FieldPlayer& operator=(const FieldPlayer&& _Other) noexcept = delete;

	inline std::shared_ptr<class GameEngineSpriteRenderer> GetRenderer() const
	{
		return RendererPtr;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	static FieldPlayer* GPtr;

	PlayerFSM Fsm;
	std::shared_ptr<class GameEngineSpriteRenderer> RendererPtr = nullptr;
};

