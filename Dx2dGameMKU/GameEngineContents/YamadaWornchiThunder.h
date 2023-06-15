#pragma once
#include <GameEngineCore/GameEngineActor.h>

class YamadaWornchiThunder : public GameEngineActor
{
public:
	YamadaWornchiThunder();
	~YamadaWornchiThunder() override;

	YamadaWornchiThunder(const YamadaWornchiThunder& _Other) = delete;
	YamadaWornchiThunder(YamadaWornchiThunder&& _Other) noexcept = delete;
	YamadaWornchiThunder& operator=(const YamadaWornchiThunder& _Other) = delete;
	YamadaWornchiThunder& operator=(const YamadaWornchiThunder&& _Other) noexcept = delete;

protected:

private:

};

