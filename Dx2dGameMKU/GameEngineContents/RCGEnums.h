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



//BossVersus������ �����, �Ƹ� FSM������ �̷��� �ܺη� �������� ����
enum class BossType
{
	Misuzu,
	Yamada,
	Noise
};


