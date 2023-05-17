#pragma once


enum class UpdateOrder
{
	Defalut = 0,
	BackGround,
	FieldDoor,
	Player,
	Enemy,

	UI,
};

enum class CollisionOrder
{
	PlayerMain,
	PlayerAttack,
	EnemyMain,
	EnemyAttack,
};



//BossVersus에서만 사용중, 아마 FSM때문에 이렇게 외부로 뻬놓은거 같음
enum class BossType
{
	Misuzu,
	Yamada,
	Noise
};


