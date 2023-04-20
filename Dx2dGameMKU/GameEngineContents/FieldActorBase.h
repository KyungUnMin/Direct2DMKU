#pragma once


class FieldActorBase
{
public:
	FieldActorBase();
	~FieldActorBase();

	FieldActorBase(const FieldActorBase& _Other) = delete;
	FieldActorBase(FieldActorBase&& _Other) noexcept = delete;
	FieldActorBase& operator=(const FieldActorBase& _Other) = delete;
	FieldActorBase& operator=(const FieldActorBase&& _Other) noexcept = delete;

protected:

private:

};

