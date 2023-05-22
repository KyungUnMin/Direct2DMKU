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

//enum class RenderOrder
//{
//	Defalut = 0,
//	BackGround,
//	Debug_MapCol,
//	Shadow,
//	Character,
//	Effect,
//
//	Door,
//	Debug_Grid
//};

enum class FieldRenderOrder
{
	BackGround,
	Debug_MapCol,
	ZOrder,

	Debug_Grid
};



//BossVersus������ �����, �Ƹ� FSM������ �̷��� �ܺη� �������� ����
enum class BossType
{
	Misuzu,
	Yamada,
	Noise
};


