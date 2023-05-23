#pragma once


class FileCopier
{
public:
	FileCopier(const FileCopier& _Other) = delete;
	FileCopier(FileCopier&& _Other) noexcept = delete;
	FileCopier& operator=(const FileCopier& _Other) = delete;
	FileCopier& operator=(const FileCopier&& _Other) noexcept = delete;


	//static void Copy(const GameEngineDirectory& _Dir)

	static void FileCopy(const std::string_view& _ChangeName);



protected:

private:
	FileCopier();
	virtual ~FileCopier() = 0;


};

