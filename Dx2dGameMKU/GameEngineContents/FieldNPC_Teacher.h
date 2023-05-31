#pragma once
#include "FieldNPCBase.h"

class FieldNPC_Teacher : public FieldNPCBase
{
public:
	FieldNPC_Teacher();
	~FieldNPC_Teacher() override;

	FieldNPC_Teacher(const FieldNPC_Teacher& _Other) = delete;
	FieldNPC_Teacher(FieldNPC_Teacher&& _Other) noexcept = delete;
	FieldNPC_Teacher& operator=(const FieldNPC_Teacher& _Other) = delete;
	FieldNPC_Teacher& operator=(const FieldNPC_Teacher&& _Other) noexcept = delete;

protected:
	void Start() override;


private:

};

