#include "PrecompileHeader.h"
#include "DyingMessage.h"




const std::vector<std::string_view> DyingMessage::MsgOwnerNames =
{
	"���л� : ",			//SchoolBoy
	"���л� : ",			//SchoolGirl
	"ġ��� : ",			//Cheerleader
	"���� : ",				//Cop
	"�ҷ��� : ",			//Hooligan
	"Ÿ�̰Ÿ� : ",			//TigerMan
	"�˹ٻ� : ",			//Waver
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
		"�� �� ����",
		"����..!",
		"��¥ ����.",
		"�;�!",
		"����!",
		"������",
		"�����!",
		"��!",
		"����!",
		"�����!",
	},

	//SchoolGirl
	{
		"�� ��¥!",
		"��!",
		"�״�� �� ���ڴϱ�.",
		"�սΰ���",
		"�ѽ��� ������!",
		"�ѽ���",
	},

	//Cheerleader
	{
		"����..",
		"���� ����.",
		"��!",
		"�Ⱦ�!",
		"�����ƾƾ�!",
		"�ƺ�!",
		"������ ��!",
		"�� ���� ��",
	},

	//Cop
	{
		"ũ��!",
		"�̰� �ƴ���.",
		"���� �����ϱ�",
		"����!",
	},

	//Hooligan
	{
		"�Ǽ���",
		"�������״�",
		"�̰� ��ճ�?",
		"���� ���� �԰ڱ�",
		"�Ʊ� ���� ����!",
		"�� ���Ͻó�",
		"����",
		"����!",
		"�Ͼ�..",
		"������!",
		"�������� ��ȭ�� �ؾ���",
	},

	//TigerMan
	{
		"���� ��·�ٰ�?",
	},

	//Waver
	{
		"����..",
		"�谡!",
		"�����!",
		"�ƺ�!",
		"�Ǹ��̾�",
		"�� ��� ���»�� �־�?",
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

