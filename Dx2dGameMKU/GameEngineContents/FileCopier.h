#pragma once


class FileCopier
{
public:
	FileCopier(const FileCopier& _Other) = delete;
	FileCopier(FileCopier&& _Other) noexcept = delete;
	FileCopier& operator=(const FileCopier& _Other) = delete;
	FileCopier& operator=(const FileCopier&& _Other) noexcept = delete;


	//static void Copy(const GameEngineDirectory& _Dir)

	static void Test(/*GameEngineDirectory _Dir*/);

protected:

private:
	FileCopier();
	virtual ~FileCopier() = 0;

};

