#include "PrecompileHeader.h"
#include "GameEngineActorGUI.h"
#include <GameEngineCore/GameEngineLevel.h>

GameEngineActorGUI::GameEngineActorGUI()
{
}

GameEngineActorGUI::~GameEngineActorGUI()
{
}

void GameEngineActorGUI::Start()
{
	ImGui::SetWindowSize(GetName().data(), ImVec2(300, 150));
}

void GameEngineActorGUI::OnGUI(std::shared_ptr<GameEngineLevel>, float _DeltaTime)
{
	if (nullptr == TargetTransform)
	{
		return;
	}

	if (true == TargetTransform->IsDeath())
	{
		TargetTransform = nullptr;
		return;
	}
	
	ImGui::Checkbox("W", &IsWorldPostion);
	ImGui::SameLine();
	HelpMarker("Setting World Postion");
	ImGui::SameLine();

	float4 GetPostion = float4::Zero; 

	if (true == IsWorldPostion)
	{
		TargetTransform->SetWorldPosition(TargetTransform->GetWorldPosition());
		GetPostion = TargetTransform->GetWorldPosition();
	}
	else
	{
		TargetTransform->SetLocalPosition(TargetTransform->GetLocalPosition());
		GetPostion = TargetTransform->GetLocalPosition();
	}

	Postion[0] = GetPostion.x;
	Postion[1] = GetPostion.y;
	Postion[2] = GetPostion.z;
	Postion[3] = GetPostion.w;

	ImGui::DragFloat4(" - Postion", Postion);

	if (true == IsWorldPostion)
	{
		TargetTransform->SetWorldPosition(ConvertFloat4(Postion));
	}
	else
	{
		TargetTransform->SetLocalPosition(ConvertFloat4(Postion));
	}

	ImGui::Checkbox("W", &IsWorldRotation);
	ImGui::SameLine();
	HelpMarker("Setting World Rotation");
	ImGui::SameLine();

	float4 GetRoation = float4::Zero;

	if (true == IsWorldPostion)
	{
		TargetTransform->SetWorldRotation(TargetTransform->GetWorldRotation());
		GetRoation = TargetTransform->GetWorldRotation();
	}
	else
	{
		TargetTransform->SetLocalRotation(TargetTransform->GetLocalRotation());
		GetRoation = TargetTransform->GetLocalRotation();
	}

	Rotation[0] = GetRoation.x;
	Rotation[1] = GetRoation.y;
	Rotation[2] = GetRoation.z;
	Rotation[3] = GetRoation.w;

	ImGui::DragFloat4(" - Rotation", Rotation);

	if (true == IsWorldRotation)
	{
		TargetTransform->SetWorldRotation(ConvertFloat4(Rotation));
	}
	else
	{
		TargetTransform->SetLocalRotation(ConvertFloat4(Rotation));
	}

	ImGui::Checkbox("W", &IsWorldScale);
	ImGui::SameLine();
	HelpMarker("Setting World Scale");
	ImGui::SameLine();

	float4 GetScale = float4::Zero;

	if (true == IsWorldScale)
	{
		TargetTransform->SetWorldScale(TargetTransform->GetWorldScale());
		GetScale = TargetTransform->GetWorldScale();
	}
	else
	{
		TargetTransform->SetLocalScale(TargetTransform->GetLocalScale());
		GetScale = TargetTransform->GetLocalScale();
	}

	Scale[0] = GetScale.x;
	Scale[1] = GetScale.y;
	Scale[2] = GetScale.z;
	Scale[3] = GetScale.w;

	ImGui::DragFloat4(" - Scale", Scale);

	if (true == IsWorldScale)
	{
		TargetTransform->SetWorldScale(ConvertFloat4(Scale));
	}
	else
	{
		TargetTransform->SetLocalScale(ConvertFloat4(Scale));
	}

	for (std::function<void()>& _CallbackRef: CustomActorGuiFunctions)
	{	

		if (nullptr == _CallbackRef)
		{
			MsgAssert("- nullptr 커스텀 Gui 콜백을 호출하려 했습니다");
			return;
		}

		ImGui::Spacing();
		ImGui::Spacing();

		_CallbackRef();
	}
}

void GameEngineActorGUI::SetTarget(GameEngineTransform* _Target)
{
	CustomActorGuiFunctions.clear();
	TargetTransform = _Target;

	if (nullptr != TargetTransform)
	{
		IsWorldPostion = false;
		IsWorldRotation = false;
		IsWorldScale = false;

		float4 LocalPos = TargetTransform->GetLocalPosition();
		float4 LocalRotation = TargetTransform->GetLocalRotation();
		float4 LocalScale = TargetTransform->GetLocalScale();

		Postion[0] = LocalPos.x;
		Postion[1] = LocalPos.y;
		Postion[2] = LocalPos.z;
		Postion[3] = LocalPos.w;

		Rotation[0] = LocalRotation.x;
		Rotation[1] = LocalRotation.y;
		Rotation[2] = LocalRotation.z;
		Rotation[3] = LocalRotation.w;

		Scale[0] = LocalScale.x;
		Scale[1] = LocalScale.y;
		Scale[2] = LocalScale.z;
		Scale[3] = LocalScale.w;

	}
}

void GameEngineActorGUI::HelpMarker(const std::string_view& _Text)
{
	ImGui::TextDisabled("(?)");
	if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayShort) && ImGui::BeginTooltip())
	{
		ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
		ImGui::TextUnformatted(_Text.data());
		ImGui::PopTextWrapPos();
		ImGui::EndTooltip();
	}
}

float4 GameEngineActorGUI::ConvertFloat4(float _FloatArr[4])
{
	return float4(_FloatArr[0], _FloatArr[1], _FloatArr[2], _FloatArr[3]);
}