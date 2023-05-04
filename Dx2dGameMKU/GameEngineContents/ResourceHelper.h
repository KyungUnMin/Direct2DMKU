#pragma once


class ResourceHelper
{
public:
	ResourceHelper();
	~ResourceHelper();

	ResourceHelper(const ResourceHelper& _Other) = delete;
	ResourceHelper(ResourceHelper&& _Other) noexcept = delete;
	ResourceHelper& operator=(const ResourceHelper& _Other) = delete;
	ResourceHelper& operator=(const ResourceHelper&& _Other) noexcept = delete;

	static float4 GetTextureScale(const std::string_view& _ResName);

protected:

private:

};

