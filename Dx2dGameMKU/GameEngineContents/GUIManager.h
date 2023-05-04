#pragma once

#include <typeinfo>

class GUIManager
{
public:

	GUIManager(const GUIManager& _Other) = delete;
	GUIManager(GUIManager&& _Other) noexcept = delete;
	GUIManager& operator=(const GUIManager& _Other) = delete;
	GUIManager& operator=(const GUIManager&& _Other) noexcept = delete;

	static void Init();

	template <typename ConvertType>
	static std::shared_ptr<ConvertType> Find()
	{
		const type_info& Info = typeid(ConvertType);
		std::string Name = Info.name();
		Name.replace(0, 6, "");
		return GameEngineGUI::FindGUIWindowConvert<ConvertType>(Name);
	}

protected:

private:
	template <typename ConvertType>
	static void CreateGui()
	{
		const type_info& Info = typeid(ConvertType);
		std::string Name = Info.name();
		Name.replace(0, 6, "");
		GameEngineGUI::GUIWindowCreate<ConvertType>(Name);
	}
	
	GUIManager();
	virtual ~GUIManager() = 0;
};

