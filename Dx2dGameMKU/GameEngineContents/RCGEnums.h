#pragma once


enum class UpdateOrder
{
	Defalut = 0,
	BackGround,
	FieldDoor,
	Player,
	Enemy,
	Effect,

	UI,
};

enum class CollisionOrder
{
	PlayerMain,
	PlayerAttack,
	EnemyMain,
	EnemyAttack,
};

enum class FieldRenderOrder
{
	BackGround,
	ZOrder,

	Debug_Grid
};

enum class FieldUIRenderOrder
{
	Default = 0,
	HUD,
	Fade,
};



//BossVersus에서만 사용중, 아마 FSM때문에 이렇게 외부로 뻬놓은거 같음
enum class BossType
{
	Misuzu,
	Yamada,
	Noise
};


