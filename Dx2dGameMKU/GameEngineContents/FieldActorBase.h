#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GameEngineSpriteRenderer;
class GameEngineRenderer;
class GameEngineCollision;
enum class CollisionOrder;

class FieldActorBase : public GameEngineActor
{
public:
	static void Update_CheckDebugKey();
	static void Reset_CheckDebugKey();

	FieldActorBase();
	virtual ~FieldActorBase() = 0;

	FieldActorBase(const FieldActorBase& _Other) = delete;
	FieldActorBase(FieldActorBase&& _Other) noexcept = delete;
	FieldActorBase& operator=(const FieldActorBase& _Other) = delete;
	FieldActorBase& operator=(const FieldActorBase&& _Other) noexcept = delete;

	virtual void Look(const float4& _LookPos);

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

	inline std::shared_ptr<GameEngineCollision> GetMainCollider() const
	{
		if (nullptr == MainCollider.ParentCollision)
		{
			MsgAssert("MainCollider를 만들어 준 적이 없습니다.\n FieldActorBase::CreateColliders를 호출하세요");
		}

		return MainCollider.ParentCollision;
	}

	inline std::shared_ptr<GameEngineCollision> GetAttackCollider() const
	{
		if (nullptr == MainCollider.ParentCollision)
		{
			MsgAssert("AttackCollider를 만들어 준 적이 없습니다.\n FieldActorBase::CreateColliders를 호출하세요");
		}

		return AttackCollider.ParentCollision;
	}

	inline std::shared_ptr<GameEngineSpriteRenderer> GetShadowRender() const
	{
		return ShadowRender;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	inline std::shared_ptr<class BackGround> GetBackGround() const
	{
		return BGPtr;
	}

	void CreateColliders(CollisionOrder _Order);
	

	void SetShadowScale(const float4& _ShadowScale);
	void SetShadowScale(float _Ratio);

private:
	static const float4 RenderScale;
	static const float4 CollisionColor;
	static bool IsGridPosRenderOn_ForDebug;
	static bool IsColRenderOn_ForDebug;

	float Height = 0.f;

	std::shared_ptr<class BackGround> BGPtr = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> GridPosRender_Debug = nullptr;
	std::pair<int, int> GridPos = { 0, 0 };

	std::shared_ptr<GameEngineSpriteRenderer> RendererPtr = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> ShadowRender = nullptr;



	struct VisualCollider
	{
		std::shared_ptr<GameEngineCollision> ParentCollision = nullptr;
		std::shared_ptr<GameEngineRenderer> ChildRender = nullptr;
	};


	VisualCollider MainCollider;
	VisualCollider AttackCollider;



	void CreateShadow();
	void CreateDebugGridPoint();
	VisualCollider CreateVisuableCollision(CollisionOrder _Order);
	
	void Update_GridDebug();
	void Update_ColliderView();
};

