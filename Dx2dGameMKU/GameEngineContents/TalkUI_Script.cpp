#include "PrecompileHeader.h"
#include "TalkUI.h"

const std::vector<std::vector<TextUI_ScripteInfo>> TalkUI::AllTalkScript =
{
	//Godai1
	{
		{"Conversation_Godai1.png", "����! �Ա�!", "����� : ",false},
		{"Conversation_Kyoko6.png", "���......!", "���� : ",true},
		{"Conversation_Misako2.png", "������! ����! �ϸ��͸� �� �Ӹ��� ������ ���߾�", "�̻��� : ",true},
		{"Conversation_Godai2.png", "�� �� ���°� �Ƴ�, ����̶�!", "����� : ",false},
		{"Conversation_Misako1.png", "�� �̸� �ȴٰ� ���� �޶���?", "�̻��� : ",true},
		{"Conversation_Godai4.png", "�ʵ��б� 3�г� ������ �̿����ݾ�", "����� : ",false},
		{"Conversation_Kyoko3.png", "��, �´�! �̻���. �� ����, ���� ������ ���� ���ݾ�", "���� : ",true},
		{"Conversation_Misako4.png", "��, �ʱ���....", "�̻��� : ",true},
		{"Conversation_Kyoko5.png", "���� �豸�� �� ������ ���� ��� �б����� �߷ȴٰ� ����µ�", "���� : ",true},
		{"Conversation_Godai3.png", "����, ����? ����, ��, ��·��.. ���� ���� ����? ���� ������ ��?", "����� : ",false},
		{"Conversation_Misako5.png", "�����, ������ ����?", "�̻��� : ",true},
		{"Conversation_Godai2.png", "���� ���� ���� �־���...", "����� : ",false},
		{"Conversation_Kyoko6.png", "���� �־���? ¡�׷�..", "���� : ",true},
		{"Conversation_Godai1.png", "....���� ������ �� �����ž�. ��Ű�ϰ� ��Ͽ��� ã�� ����?", "����� : ",false},
		{"Conversation_Godai1.png", "��� �� ���� ������� �����ϰ� �ľ��ϰ� �ְŵ�", "����� : ",false},
		{"Conversation_Kyoko1.png", "���� �츮 ��Ű�� �����ߴ��� �˾�?", "���� : ",true},
		{"Conversation_Godai7.png", "���� ����! ������ �ݹ� ã�Ƴ� �ž�, ��! �׵���.. �� �� ������", "����� : ",false},
		{"Conversation_Misako1.png", "������ ����?", "�̻��� : ",true},
		{"Conversation_Godai2.png", "�켱, �谡 ���� �����ŵ�, ���� �� ���� �� �����", "����� : ",false},
		{"Conversation_Misako2.png", "��������!", "�̻��� : ",true},
		{"Conversation_Kyoko4.png", "��¥, �ٷ� �����ݾ�", "���� : ",true},
		{"Conversation_Godai1.png", "�¾�! ���� �� ���Ÿ� ��� �ָ�, �Ż����� �׼��� ������ ���� ��ٸ��ž�", "����� : ",false},
		{"Conversation_Godai1.png", "�ֳĸ� �� �Ż�ϱ�. �˾���?", "����� : ",false},
		{"Conversation_Misako5.png", "����...", "�̻��� : ",true},
	},

	//Godai2
	{
		{"Conversation_Misako3.png", "��, �� �ܹ���.", "�̻��� : ",true},
		{"Conversation_Godai5.png", "��������, ���� ������ �ż��� ��!!", "����� : ",false},
		{"Conversation_Kyoko5.png", "�� �� �ٽ� �н�ƮǪ��� �� �԰ھ�. ��.", "���� : ",true},
		{"Conversation_Misako5.png", "��, �������� ���ŵ� �������ݾ�. ��, ��Ͽ��� ��Ű�� ���� �ƴ°� ����?", "�̻��� : ",true},
		{"Conversation_Godai1.png", "�ƾ�, �Ǹ��� �ܹ��ſ���.", "����� : ",false},
		{"Conversation_Godai4.png", "������, �����, �� ����� ��� ���� ������ϰ� �ֱ��ϰ� �־��ٰ� ����?", "����� : ",false},
		{"Conversation_Misako1.png", "�ƴ�.. �׷� �� �� �߾�", "�̻��� : ",true},
		{"Conversation_Kyoko3.png", "��� �˾�?", "���� : ",true},
		{"Conversation_Godai3.png", "��, �׾� ��, �ҹ��̶� �� ���ݾ�!", "����� : ",false},
		{"Conversation_Godai2.png", "��, ·, ��, �� �������δ� �� �� �߸����ϰ� ����ϰ� �־��� �� ����", "����� : ",false},
		{"Conversation_Misako1.png", "������ �װ�?", "�̻��� : ",true},
		{"Conversation_Godai7.png", "�ú��п� �л��̾�. �� �װ͵� �� �༮�� �װ� ������ �� �����.", "����� : ",false},
		{"Conversation_Godai3.png", "�׷�, �渶�� ���̾�", "����� : ",false},
		{"Conversation_Misako4.png", "�׷��� ����", "�̻��� : ",true},
		{"Conversation_Godai2.png", "�װ� �ְŵ�, ��·��, �߸��ٴ� ���� ���� �����ϱ�, ���� �ִ��� ���� �����.", "����� : ",false},
		{"Conversation_Kyoko1.png", "����! (�ӼӸ�)�̻���, ���� ���⼭ ������...", "���� : ",true},
		{"Conversation_Godai1.png", "�� �ǰ� �����Ҳ�! �Ҳ�ģ�� ����̸� ���� ������!", "����� : ",false},
	},

	//Godai3
	{
		{"Conversation_Godai2.png", "���� �� ���Ŵ� �����Ծ�?", "����� : ",false},
		{"Conversation_Kyoko5.png", "�ƴ�, ����.", "���� : ",true},
		{"Conversation_Godai4.png", "�ܹ��� ���� �������� ��� ���� �־�", "����� : ",false},
		{"Conversation_Misako5.png", "�˾Ҿ�", "�̻��� : ",true},
	},

	//Brunov
	{
		{"Conversation_Kyoko2.png", "�츮 VIPƼ�� �־�!", "���� : ",true},
		{"Conversation_Misako3.png", "�¾�! �׷��ϱ� ������!", "�̻��� : ",true},
		{"Conversation_Brunov2.png", "�̰�, ��¥ �¾�?", "����� : ",false},
		{"Conversation_Misako5.png", "��¥�� ��¥��", "�̻��� : ",true},
		{"Conversation_Misako2.png", "�׷��� �����ϰڴٸ�, �츮�� �ָ����� ��¥�� �� �����ٲ���!", "�̻��� : ",true},
		{"Conversation_Brunov3.png", "��ŵ��� �ָԵ� ��¥ �³���?", "����� : ",false},
		{"Conversation_Kyoko1.png", "����, ����, �츮 ��¥ ���ؿ�.", "���� : ",true},
		{"Conversation_Kyoko2.png", "�������� ���� �����̶�, ù��° ���� ��ġ�� ���� �ʾҾ��", "���� : ",true},
		{"Conversation_Brunov1.png", "Ƽ���� ��������. �ܼ�Ʈ. ��հ� ��.", "����� : ",false},
	},

	//{"AAAA.png", "TEST", "",true},
	//{"AAAA.png", "TEST", "����� : ",false},
};