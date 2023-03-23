#pragma once


class GitTestCheck
{
public:
	GitTestCheck();
	~GitTestCheck();

	GitTestCheck(const GitTestCheck& _Other) = delete;
	GitTestCheck(GitTestCheck&& _Other) noexcept = delete;
	GitTestCheck& operator=(const GitTestCheck& _Other) = delete;
	GitTestCheck& operator=(const GitTestCheck&& _Other) noexcept = delete;

protected:

private:

};

