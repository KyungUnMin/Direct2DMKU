#include "PrecompileHeader.h"
#include "GameEngineFile.h"
#include "GameEngineDebug.h"

GameEngineFile::GameEngineFile()
{

}

GameEngineFile::~GameEngineFile()
{

}

GameEngineFile::GameEngineFile(std::filesystem::path _Path)
	:Path(_Path)
{
}

void GameEngineFile::SaveBin(const GameEngineSerializer& _Data)
{
	FILE* FilePtr = nullptr;

	//������ ������ ������ string���� �޾ƿ���
	std::string PathString = Path.GetFullPath();
	//����Ʈ���� ���� ���� ����
	std::string Text = "wb";

	fopen_s(&FilePtr, PathString.c_str(), Text.c_str());

	if (nullptr == FilePtr)
	{
		MsgAssert("���� ���¿� �����Ͽ����ϴ� : " + PathString);
		return;
	}

	//_Data.GetConstData() ��ġ�� ����
	//_Data.GetOffset()��ŭ
	//�ѹ���
	//FilePtr�� ����Ű�� ���Ͽ� ����ض�
	fwrite(_Data.GetConstData(), _Data.GetOffset(), 1, FilePtr);

	if (nullptr != FilePtr)
	{
		fclose(FilePtr);
	}
}

void GameEngineFile::SaveText(const std::string_view& _View)
{
	FILE* FilePtr = nullptr;

	//������ ������ ������ string���� �޾ƿ���
	std::string PathString = Path.GetFullPath();
	//�ؽ�Ʈ���� ���� ���� ����
	std::string Text = "wt";

	fopen_s(&FilePtr, PathString.c_str(), Text.c_str());

	if (nullptr == FilePtr)
	{
		MsgAssert("���� ���¿� �����Ͽ����ϴ� : " + PathString);
		return;
	}

	//_View.data() ��ġ�� ����
	//_View.size()��ŭ
	//�ѹ���
	//FilePtr�� ����Ű�� ���Ͽ� ����ض�
	fwrite(_View.data(), _View.size(), 1, FilePtr);

	if (nullptr != FilePtr)
	{
		fclose(FilePtr);
	}
}

void GameEngineFile::LoadBin(GameEngineSerializer& _Data)
{
	FILE* FilePtr = nullptr;

	//���� ������ ������ string���� �޾ƿ���
	std::string PathString = Path.GetFullPath();
	//����Ʈ�б� ���� ���� ����
	std::string Text = "rb";

	fopen_s(&FilePtr, PathString.c_str(), Text.c_str());

	if (nullptr == FilePtr)
	{
		MsgAssert("���� ���¿� �����Ͽ����ϴ� : " + PathString);
		return;
	}

	//������ ũ�� �˾ƿ���
	size_t FileSize = std::filesystem::file_size(Path.Path);

	fread_s(_Data.GetData(), _Data.GetBufferSize(), FileSize, 1, FilePtr);

	if (nullptr != FilePtr)
	{
		fclose(FilePtr);
	}
}

