#pragma once
#include "UIBase.h"
#include "PhoneFSM.h"

class GameEngineUIRenderer;
class ShaderUIRenderer;

class HandPhoneUI : public UIBase
{
public:
	HandPhoneUI();
	~HandPhoneUI() override;

	HandPhoneUI(const HandPhoneUI& _Other) = delete;
	HandPhoneUI(HandPhoneUI&& _Other) noexcept = delete;
	HandPhoneUI& operator=(const HandPhoneUI& _Other) = delete;
	HandPhoneUI& operator=(const HandPhoneUI&& _Other) noexcept = delete;

	void Open();

	void ChangePhoneTexture(const std::string_view& _TexName);

	float4& GetBackImgColor()
	{
		return BackImgColor;
	}


protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	PhoneFSM Fsm;

	std::shared_ptr<ShaderUIRenderer> BackImg = nullptr;
	float4 BackImgColor = float4::Null;

	std::shared_ptr<GameEngineUIRenderer> PhoneLayout = nullptr;

	void LoadImgResAll();
	void CreateRenders();
};

