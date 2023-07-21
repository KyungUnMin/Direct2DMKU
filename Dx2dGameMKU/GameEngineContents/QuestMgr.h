#pragma once


class QuestMgr
{
public:
	QuestMgr();
	~QuestMgr();

	QuestMgr(const QuestMgr& _Other) = delete;
	QuestMgr(QuestMgr&& _Other) noexcept = delete;
	QuestMgr& operator=(const QuestMgr& _Other) = delete;
	QuestMgr& operator=(const QuestMgr&& _Other) noexcept = delete;

protected:

private:

};

