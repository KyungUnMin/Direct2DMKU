#pragma once
#include "StateBase.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineSprite.h>

#include "RCGDefine.h"

enum class KeyNames;
class GameEngineSpriteRenderer;
class GameEngineCollision;
class GameEngineSprite;
class AnimationInfo;

class PlayerStateBase : public StateBase
{
public:
	PlayerStateBase();
	virtual ~PlayerStateBase() = 0;

	PlayerStateBase(const PlayerStateBase& _Other) = delete;
	PlayerStateBase(PlayerStateBase&& _Other) noexcept = delete;
	PlayerStateBase& operator=(const PlayerStateBase& _Other) = delete;
	PlayerStateBase& operator=(const PlayerStateBase&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	inline std::shared_ptr<GameEngineSpriteRenderer> GetRenderer()
	{
		return Renderer;
	}

	/*inline void DirChangeOn()
	{
		DirChangeSwitch = true;
	}*/

	//�ش� ������Ʈ�� �������϶� �÷��̾��� ������ȯ�� ������
	inline void DirChangeOff()
	{
		DirChangeSwitch = false;
	}

private:
	//�÷��̾��� ���� �˻� ����
	bool DirChangeSwitch = true;

	std::shared_ptr<GameEngineSpriteRenderer> Renderer = nullptr;
	std::shared_ptr<GameEngineCollision> Collider = nullptr;

	void SettingHeightRender();
	void SettingDirectionRender();
};

