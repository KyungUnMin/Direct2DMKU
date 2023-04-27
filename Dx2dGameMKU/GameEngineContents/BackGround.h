#pragma once
#include <GameEngineCore/GameEngineActor.h>

class BackGround : public GameEngineActor
{
public:
	BackGround();
	~BackGround() override;

	BackGround(const BackGround& _Other) = delete;
	BackGround(BackGround&& _Other) noexcept = delete;
	BackGround& operator=(const BackGround& _Other) = delete;
	BackGround& operator=(const BackGround&& _Other) noexcept = delete;

	void AddBackImg(const std::string_view& _ResName, const float4& _Scale, const float4& _Offset = float4::Zero);

protected:
	void Start() override;

private:

};

