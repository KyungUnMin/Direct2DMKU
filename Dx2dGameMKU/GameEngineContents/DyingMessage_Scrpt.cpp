#include "PrecompileHeader.h"
#include "DyingMessage.h"




const std::vector<std::string_view> DyingMessage::MsgOwnerNames =
{
	"남학생 : ",			//SchoolBoy
	"여학생 : ",			//SchoolGirl
	"치어리더 : ",			//Cheerleader
	"경찰 : ",				//Cop
	"불량배 : ",			//Hooligan
	"타이거맨 : ",			//TigerMan
	"알바생 : ",			//Waver
	"",							//Misuzu
	"",							//Yamada
	"",							//Noise
	"",							//NoiseFan
};


const std::vector<float4> DyingMessage::MsgColors =
{
	float4{0.0f,		0.32f,		1.0f,			1.0f},		//SchoolBoy
	float4{1.0f,		0.0f,			1.0f,			0.86f},		//SchoolGirl
	float4{1.0f,		0.89f,		0.0f,			1.0f},		//Cheerleader
	float4{0.7f,		0.7f,			0.7f,			1.0f},		//Cop
	float4{1.0f,		0.36f,		0.0f,			1.0f},		//Hooligan
	float4{1.0f,		0.0f,			0.0f,			1.0f},		//TigerMan
	float4{0.11f,	0.85f,		0.08f,		1.0f},		//Waver
	float4{1.0f,		1.0f,			1.0f,			1.0f},		//Misuzu
	float4{1.0f,		1.0f,			1.0f,			1.0f},		//Yamada
	float4{1.0f,		1.0f,			1.0f,			1.0f},		//Noise
	float4{0.65f,	0.28f,		1.0f,			1.0f},		//NoiseFan
};


const std::vector<std::vector<std::string_view>> DyingMessage::MsgScript =
{
	//SchoolBoy
	{
		"할 수 없지",
		"젠장..!",
		"진짜 아퍼.",
		"와아!",
		"으윽!",
		"나빴어",
		"살려줘!",
		"흠!",
		"엄마!",
		"제기랄!",
	},

	//SchoolGirl
	{
		"아 진짜!",
		"흥!",
		"그대로 난 예쁘니까.",
		"왕싸가지",
		"한심한 머저리!",
		"한심해",
	},

	//Cheerleader
	{
		"으윽..",
		"등이 아파.",
		"흥!",
		"싫어!",
		"엄마아아아!",
		"아빠!",
		"때리지 마!",
		"피 맛이 나",
	},

	//Cop
	{
		"크헉!",
		"이건 아니지.",
		"정말 무례하군",
		"으윽!",
	},

	//Hooligan
	{
		"실수다",
		"복수할테다",
		"이게 재밌냐?",
		"외출 금지 먹겠군",
		"아까 먹은 밥이!",
		"좀 심하시네",
		"우웩",
		"워우!",
		"하아..",
		"무릎이!",
		"문명인은 대화를 해야지",
	},

	//TigerMan
	{
		"내가 어쨌다고?",
	},

	//Waver
	{
		"아파..",
		"배가!",
		"억울해!",
		"아빠!",
		"실망이야",
		"이 대사 보는사람 있어?",
	},

	//Misuzu
	{
		"",
	},

	//Yamada
	{
		"",
	},

	//Noise
	{
		"",
	},

	//NoiseFan
	{
		"",
	},
};

