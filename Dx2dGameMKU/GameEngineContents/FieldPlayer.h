#pragma once
#include "FieldActorBase.h"
#include "PlayerFSM.h"

class FieldPlayer : public FieldActorBase
{
	friend class FieldLevelBase;

public:
	static std::shared_ptr<FieldPlayer> GetPtr()
	{
		if (nullptr == GPtr)
		{
			MsgAssert("아직 실행중인 플레이어가 존재하지 않습니다");
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

	inline bool IsDashing() const
	{
		return (PlayerStateType::Dash == Fsm.GetNowState<PlayerStateType>());
	}

	inline const std::pair<int, int>& GetGridPos() const
	{
		return GridPos;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	//레벨쪽에서 매 프레임마다 실행중인 플레이어를 설정해준다
	static FieldPlayer* GPtr;

	PlayerFSM Fsm;
	std::shared_ptr<class GameEngineSpriteRenderer> RendererPtr = nullptr;
	std::shared_ptr<class BackGround> BGPtr = nullptr;
	std::pair<int, int> GridPos = { 0, 0 };

	std::shared_ptr<GameEngineSpriteRenderer> GridPosRender_Debug = nullptr;

	void CreateDebugGridPoint();
	void CreateRender();
	void Update_GridRender_Debug();
};

