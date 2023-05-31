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
	FOR_DEBUG		//나중에 반드시 지워야 할 애들
};

enum class CollisionOrder
{
	PlayerMain,
	PlayerAttack,
	EnemyMain,
	EnemyAttack,
	NPC,
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

	BossVersus,
	BossIntro,
};

enum class ShopUIRenderOrder
{
	Default = 0,

	Info,
	Cursor,
	Item,
};



//BossVersus에서만 사용중, 아마 FSM때문에 이렇게 외부로 뻬놓은거 같음
enum class BossType
{
	Misuzu,
	Yamada,
	Noise
};


