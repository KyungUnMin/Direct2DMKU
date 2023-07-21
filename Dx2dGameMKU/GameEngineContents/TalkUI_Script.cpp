#include "PrecompileHeader.h"
#include "TalkUI.h"

const std::vector<std::vector<TextUI_ScripteInfo>> TalkUI::AllTalkScript =
{
	//Godai1
	{
		{"Conversation_Godai1.png", "여어! 왔군!", "고다이 : ",false},
		{"Conversation_Kyoko6.png", "우와......!", "쿄코 : ",true},
		{"Conversation_Misako2.png", "조심해! 변태! 하마터면 네 머리를 뜯어버릴 뻔했어", "미사코 : ",true},
		{"Conversation_Godai2.png", "아 난 변태가 아냐, 고다이라구!", "고다이 : ",false},
		{"Conversation_Misako1.png", "네 이름 안다고 뭐가 달라져?", "미사코 : ",true},
		{"Conversation_Godai4.png", "초등학교 3학년 때부터 이웃이잖아", "고다이 : ",false},
		{"Conversation_Kyoko3.png", "아, 맞다! 미사코. 이 변태, 너희 집에서 가까운데 살잖아", "쿄코 : ",true},
		{"Conversation_Misako4.png", "아, 너구나....", "미사코 : ",true},
		{"Conversation_Kyoko5.png", "여자 배구부 팀 사진을 몰래 찍다 학교에서 잘렸다고 들었는데", "쿄코 : ",true},
		{"Conversation_Godai3.png", "누구, 내가? 하하, 어, 어쨌든.. 오늘 날씨 좋지? 요즘 스포츠 봐?", "고다이 : ",false},
		{"Conversation_Misako5.png", "고다이, 목적이 뭐야?", "미사코 : ",true},
		{"Conversation_Godai2.png", "너희 둘을 보고 있었어...", "고다이 : ",false},
		{"Conversation_Kyoko6.png", "보고 있었어? 징그러..", "쿄코 : ",true},
		{"Conversation_Godai1.png", "....내가 도와줄 수 있을거야. 리키하고 쿠니오를 찾고 있지?", "고다이 : ",false},
		{"Conversation_Godai1.png", "사실 난 많은 사람들을 관찰하고 파악하고 있거든", "고다이 : ",false},
		{"Conversation_Kyoko1.png", "누가 우리 리키를 유괴했는지 알아?", "쿄코 : ",true},
		{"Conversation_Godai7.png", "아직 몰라! 하지만 금방 찾아낼 거야, 꼭! 그동안.. 날 좀 도와줘", "고다이 : ",false},
		{"Conversation_Misako1.png", "목적이 뭐야?", "미사코 : ",true},
		{"Conversation_Godai2.png", "우선, 배가 많이 고프거든, 더블 텍 버거 좀 사다줘", "고다이 : ",false},
		{"Conversation_Misako2.png", "게으르긴!", "미사코 : ",true},
		{"Conversation_Kyoko4.png", "진짜, 바로 저기잖아", "쿄코 : ",true},
		{"Conversation_Godai1.png", "맞아! 더블 텍 버거를 사다 주면, 신사적인 액수의 보상이 너희를 기다릴거야", "고다이 : ",false},
		{"Conversation_Godai1.png", "왜냐면 난 신사니까. 알았지?", "고다이 : ",false},
		{"Conversation_Misako5.png", "으엑...", "미사코 : ",true},
	},

	//Godai2
	{
		{"Conversation_Misako3.png", "자, 네 햄버거.", "미사코 : ",true},
		{"Conversation_Godai5.png", "오오오오, 구운 쇠고기의 신성한 맛!!", "고다이 : ",false},
		{"Conversation_Kyoko5.png", "두 번 다시 패스트푸드는 못 먹겠어. 나.", "쿄코 : ",true},
		{"Conversation_Misako5.png", "자, 거지같은 버거도 갖다줬잖아. 자, 쿠니오랑 리키에 대해 아는게 뭐야?", "미사코 : ",true},
		{"Conversation_Godai1.png", "아아, 훌륭한 햄버거였어.", "고다이 : ",false},
		{"Conversation_Godai4.png", "오케이, 너희들, 두 사람이 기분 나쁜 사람들하고 애기하고 있었다고 했지?", "고다이 : ",false},
		{"Conversation_Misako1.png", "아니.. 그런 말 안 했어", "미사코 : ",true},
		{"Conversation_Kyoko3.png", "어떻게 알아?", "쿄코 : ",true},
		{"Conversation_Godai3.png", "아, 그야 뭐, 소문이란 게 있잖아!", "고다이 : ",false},
		{"Conversation_Godai2.png", "어, 쨌, 든, 내 추측으로는 둘 다 야마다하고 얘기하고 있었던 것 같아", "고다이 : ",false},
		{"Conversation_Misako1.png", "누구야 그게?", "미사코 : ",true},
		{"Conversation_Godai7.png", "냉봉학원 학생이야. 뭐 그것도 그 녀석이 그걸 익히기 전 얘기지.", "고다이 : ",false},
		{"Conversation_Godai3.png", "그래, 흑마술 말이야", "고다이 : ",false},
		{"Conversation_Misako4.png", "그런건 없어", "미사코 : ",true},
		{"Conversation_Godai2.png", "그게 있거든, 어쨌든, 야마다는 거의 몰에 있으니까, 놈이 있는지 가서 보라고.", "고다이 : ",false},
		{"Conversation_Kyoko1.png", "고마워! (귓속말)미사코, 빨리 여기서 나가자...", "쿄코 : ",true},
		{"Conversation_Godai1.png", "잘 되게 응원할께! 소꿉친구 고다이를 잊지 말아줘!", "고다이 : ",false},
	},

	//Godai3
	{
		{"Conversation_Godai2.png", "더블 텍 버거는 가져왔어?", "고다이 : ",false},
		{"Conversation_Kyoko5.png", "아니, 아직.", "쿄코 : ",true},
		{"Conversation_Godai4.png", "햄버거 집은 우측으로 계속 가면 있어", "고다이 : ",false},
		{"Conversation_Misako5.png", "알았어", "미사코 : ",true},
	},

	//Brunov
	{
		{"Conversation_Kyoko2.png", "우리 VIP티켓 있어!", "쿄코 : ",true},
		{"Conversation_Misako3.png", "맞아! 그러니까 비켜줘!", "미사코 : ",true},
		{"Conversation_Brunov2.png", "이거, 진짜 맞아?", "브루노브 : ",false},
		{"Conversation_Misako5.png", "진짜로 진짜야", "미사코 : ",true},
		{"Conversation_Misako2.png", "그래도 방해하겠다면, 우리의 주먹으로 진짜란 걸 보여줄꺼야!", "미사코 : ",true},
		{"Conversation_Brunov3.png", "당신들의 주먹도 진짜 맞나요?", "브루노브 : ",false},
		{"Conversation_Kyoko1.png", "헤헤, 오빠, 우리 진짜 급해요.", "쿄코 : ",true},
		{"Conversation_Kyoko2.png", "노이즈의 초절 빅팬이라서, 첫번째 곡을 놓치고 싶지 않았어요", "쿄코 : ",true},
		{"Conversation_Brunov1.png", "티켓은 문제없네. 콘서트. 재밌게 봐.", "브루노브 : ",false},
	},

	//{"AAAA.png", "TEST", "",true},
	//{"AAAA.png", "TEST", "브루노브 : ",false},
};