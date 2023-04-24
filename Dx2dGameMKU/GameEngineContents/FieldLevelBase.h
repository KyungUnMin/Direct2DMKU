#pragma once
#include <GameEngineCore/GameEngineLevel.h>

class FieldLevelBase : public GameEngineLevel
{
public:
	static FieldLevelBase* GetGPtr()
	{
		return GPtr;
	}

	FieldLevelBase();
	virtual ~FieldLevelBase()  = 0;

	FieldLevelBase(const FieldLevelBase& _Other) = delete;
	FieldLevelBase(FieldLevelBase&& _Other) noexcept = delete;
	FieldLevelBase& operator=(const FieldLevelBase& _Other) = delete;
	FieldLevelBase& operator=(const FieldLevelBase&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) final;

	void SettingBackImg(const std::string_view& _ResName, const float4& _MapScale);

private:
	static FieldLevelBase* GPtr;

	std::shared_ptr<class BackGround> BGPtr = nullptr;
};

