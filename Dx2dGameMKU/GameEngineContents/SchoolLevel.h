#pragma once
#include "FieldLevelBase.h"

class SchoolLevel : public FieldLevelBase
{
public:
	SchoolLevel();
	~SchoolLevel() override;

	SchoolLevel(const SchoolLevel& _Other) = delete;
	SchoolLevel(SchoolLevel&& _Other) noexcept = delete;
	SchoolLevel& operator=(const SchoolLevel& _Other) = delete;
	SchoolLevel& operator=(const SchoolLevel&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

