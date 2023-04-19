#include "PrecompileHeader.h"
#include "GameEngineDirectory.h"
#include "GameEngineFile.h"
#include "GameEngineDebug.h"
#include "GameEngineString.h"

GameEngineDirectory::GameEngineDirectory()
{
}

GameEngineDirectory::~GameEngineDirectory()
{
}


//���ڷ� ���� _String�� �ִ� �� ���� �θ� ��η� �̵�
void GameEngineDirectory::MoveParentToDirectory(const std::string_view& _String)
{
	std::string MovePath = "\\";
	MovePath += _String;

	Path.MoveParentToChildPath(MovePath.c_str());
}


//���丮 �󿡼� ���ڷ� ���� �ڽ� ��η� �̵�
bool GameEngineDirectory::Move(const std::string_view& _String)
{
	std::string MovePath = "\\";
	MovePath += _String;
	return Path.Move(MovePath.c_str());
}


//������� Path�� ���ڷ� ���� _String�� ��ģ ��θ� ���� ����� ��ȯ
GameEnginePath GameEngineDirectory::GetPlusFileName(const std::string_view& _String)
{

	std::string PathString = Path.GetPathToString();
	PathString += "\\";
	PathString += _String;

	return GameEnginePath(PathString);
}


//���丮 �󿡼� �θ� ��η� �̵�
bool GameEngineDirectory::MoveParent()
{
	if (true == Path.IsRoot())
	{
		MsgAssert("��Ʈ ���丮�� �θ���丮�� �̵��Ҽ� �����ϴ�.");
		return false;
	}

	Path.MoveParent();

	return true;
}


//�� ���Ͽ� �ִ� ��ε��� ���Ϳ� ��� ����
std::vector<GameEngineFile> GameEngineDirectory::GetAllFile(std::vector<std::string_view>_Ext)
{
	//���ڷ� ���� Ȯ���ڵ��� ���� �빮�ڷ� �ٲٱ�
	std::vector<std::string> UpperExts;
	UpperExts.reserve(_Ext.size());
	for (size_t i = 0; i < _Ext.size(); ++i)
	{
		std::string OtherUpperExt = GameEngineString::ToUpper(_Ext[i]);
		UpperExts.push_back(OtherUpperExt);
	}

	//���Ͽ� �ִ� ��θ� ��ȯ�Ҽ� �ִ� �ݺ���
	std::filesystem::directory_iterator DirIter(Path.Path);
	std::vector<GameEngineFile> Files;

	//���Ͽ� �ִ� ��ε��� ��ȸ
	for (const std::filesystem::directory_entry& Entry : DirIter)
	{
		//�ش� ��ΰ� �������� ���丮���� Ȯ��(���ϸ� ����)
		if (true == Entry.is_directory())
		{
			//���丮�� ��� ���� ��ε��� ��� ��ȸ
			GameEngineDirectory ChildDir(Entry.path());

			//�ڽĿ��� ã�� �������� �� ��ο� ����
			std::vector<GameEngineFile> ChildFiles = ChildDir.GetAllFile(_Ext);
			for (size_t i = 0; i < ChildFiles.size(); i++)
			{
				Files.push_back(ChildFiles[i]);
			}

			//ã�� ���Ŀ��� ���������� ����������(�̷��� ���ѷ���X)
			continue;
		}

		//������ ��ü ���
		std::string Path = Entry.path().string();

		//������ Ȯ���ڸ� �̾� �빮�ڷ� ��ȯ
		std::string Ext = Entry.path().extension().string();
		std::string UpperExt = GameEngineString::ToUpper(Ext);

		bool Check = false;

		//�� ������ ���ڷ� ���� Ȯ���ڵ� ���͸� ��ȸ
		for (size_t i = 0; i < UpperExts.size(); ++i)
		{
			//���� ��ȸ���� Ȯ����
			const std::string& ExtText = UpperExts[i];

			//ã���� �ϴ� Ȯ���ڰ� ���� ���� �ִ� ���
			if (ExtText == UpperExt)
			{
				Check = true;
				break;
			}
		}

		//���� ������ ���ڷ� ���� Ȯ���ڵ鿡 �ش� ���� �ʴ� ��� ���� ������ ã��
		if (false == Check)
			continue;

		//�ش� ��� ����
		Files.push_back(GameEngineFile(Entry.path()));
	}

	return Files;
}