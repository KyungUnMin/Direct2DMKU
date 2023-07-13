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

	UI,
	FOR_DEBUG		//���߿� �ݵ�� ������ �� �ֵ�
};

enum class CollisionOrder
{
	PlayerMain,
	PlayerAttack,
	EnemyMain,
	EnemyAttack,
	NPC,
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
	HUD,
	BossHUD,
	Conversation_BackImg,
	Conversation_Portrait,

	Fade,
	LevelChangeHeart,
	BossIntro,	//Boss ���� ����
};

enum class ShopUIRenderOrder
{
	Default = 0,

	Info,
	Cursor,
	Item,
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



//BossVersus������ �����, �Ƹ� FSM������ �̷��� �ܺη� �������� ����
enum class BossType
{
	Misuzu,
	Yamada,
	Noise
};


