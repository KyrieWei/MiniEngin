#include "AssetManager.h"

#include "Runtime/Resource/ConfigManager/ConfigManager.h"

namespace ME
{
	std::filesystem::path AssetManager::GetFullPath(const std::string& relative_path) const
	{
		return std::filesystem::absolute(g_runtime_global_context.m_config_manager->GetRootFolder() / relative_path);
	}
}