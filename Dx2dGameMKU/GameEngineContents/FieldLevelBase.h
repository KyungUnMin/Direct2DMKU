#pragma once


class FieldLevelBase
{
public:
	FieldLevelBase();
	~FieldLevelBase();

	FieldLevelBase(const FieldLevelBase& _Other) = delete;
	FieldLevelBase(FieldLevelBase&& _Other) noexcept = delete;
	FieldLevelBase& operator=(const FieldLevelBase& _Other) = delete;
	FieldLevelBase& operator=(const FieldLevelBase&& _Other) noexcept = delete;

protected:

private:

};

