#pragma once

#include <typeinfo>

class GUIManager
{
public:

	GUIManager(const GUIManager& _Other) = delete;
	GUIManager(GUIManager&& _Other) noexcept = delete;
	GUIManager& operator=(const GUIManager& _Other) = delete;
	GUIManager& operator=(const GUIManager&& _Other) noexcept = delete;

	/*static void Init();

	template <typename ConvertType>
	static std::shared_ptr<ConvertType> Find()
	{
		const type_info& Info = typeid(ConvertType);
		std::string Name = Info.name();
		Name.replace(0, 6, "");
		return GameEngineGUI::FindGUIWindowConvert<ConvertType>(Name);
	}*/


	template <typename ConvertType>
	static std::shared_ptr<ConvertType>  CreateGui()
	{
		const type_info& Info = typeid(ConvertType);
		std::string Name = Info.name();
		Name.replace(0, 6, "");

		if (nullptr != GameEngineGUI::FindGUIWindow(Name))
		{
			MsgAssert("해당 GUI를 다른 곳에서 만들어 준 적이 있습니다");
			return nullptr;
		}

		std::shared_ptr<GameEngineGUIWindow> GuiPtr = nullptr;
		GuiPtr = GameEngineGUI::GUIWindowCreate<ConvertType>(Name);
		return std::dynamic_pointer_cast<ConvertType>(GuiPtr);
	}


protected:

private:
	
	
	GUIManager();
	virtual ~GUIManager() = 0;
};

