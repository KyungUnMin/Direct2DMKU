#pragma once
#include <GameEngineCore/GameEngineLevel.h>

class FieldLevelBase : public GameEngineLevel
{
public:
	FieldLevelBase();
	virtual ~FieldLevelBase()  = 0;

	FieldLevelBase(const FieldLevelBase& _Other) = delete;
	FieldLevelBase(FieldLevelBase&& _Other) noexcept = delete;
	FieldLevelBase& operator=(const FieldLevelBase& _Other) = delete;
	FieldLevelBase& operator=(const FieldLevelBase&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

