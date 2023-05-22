#pragma once
#include "PlayerState_DamagedBase.h"

class PlayerState_Damaged_Block : public PlayerState_DamagedBase
{
public:
	PlayerState_Damaged_Block();
	~PlayerState_Damaged_Block() override;

	PlayerState_Damaged_Block(const PlayerState_Damaged_Block& _Other) = delete;
	PlayerState_Damaged_Block(PlayerState_Damaged_Block&& _Other) noexcept = delete;
	PlayerState_Damaged_Block& operator=(const PlayerState_Damaged_Block& _Other) = delete;
	PlayerState_Damaged_Block& operator=(const PlayerState_Damaged_Block&& _Other) noexcept = delete;

	//적에게 공격받을때 외부에서 호출시켜준다
	void OnDamage();

protected:
	void Start() override;
	void EnterState() override;
	void Update(float _DeltaTime) override;
	

private:
	struct AniInfo
	{
		std::string_view AniName = "";
		size_t Start = -1;
		size_t End = -1;
		float InterTime = 0.0f;
		bool Loop = false;
	};

	static const std::string_view AniFileName;
	static const std::vector<AniInfo> AniInfoes;

	enum class State
	{
		Block,
		Damage,
		Exit,
	};

	State CurState = State::Block;

	void LoadAnimation();
	void CreateAnimation();

	void Update_Block();
	void Update_Damage();
	void Update_Exit();
};

