#pragma once


enum class UpdateOrder
{
	Defalut = 0,
	BackGround,
	FieldDoor,
	Player,
	Enemy,
	NPC,
	Effect,
	ScreenLock,
	Money,

	UI,
	ShopItemData,
	FOR_DEBUG		//나중에 반드시 지워야 할 애들
};

enum class CollisionOrder
{
	PlayerMain,
	PlayerAttack,
	EnemyMain,
	EnemyAttack,
	NPC,
	FieldItem,
	ScreenLock,
};

enum class RCG_CamNumType
{
	Main = 0,

	UI = 100,
	BossUI = 101,
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
	ScreenChainLock,
	HUD,
	BossHUD,
	Conversation_BackImg,
	Conversation_Portrait,

	Fade,
	LevelChangeHeart,
	BossIntro,	//Boss 등장 무비
};

enum class ShopUIRenderOrder
{
	Default = 0,

	Info,
	Cursor,
	Item,
	Desc,
};

enum class BossVersusUIRenderOrder
{
	ScreenLight,
	Corner_Black,
	Portrait,
	Corner_Pink,
	Light,
	Fire,
	NameTag,
	Name,
};



//BossVersus에서만 사용중, 아마 FSM때문에 이렇게 외부로 뻬놓은거 같음
enum class BossType
{
	Misuzu,
	Yamada,
	Noise
};


