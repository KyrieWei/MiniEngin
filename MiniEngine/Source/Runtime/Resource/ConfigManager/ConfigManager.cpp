#include "ConfigManager.h"

#include <filesystem>
#include <fstream>
#include <string>

namespace ME
{
	void ConfigManager::Initialize(const std::filesystem::path& config_file_path)
	{
		//read configs
		std::ifstream config_file(config_file_path);
		std::string	config_line;
		while (std::getline(config_file, config_line))
		{
			size_t seperate_pos = config_line.find_first_of('=');
			if (seperate_pos > 0 && seperate_pos < (config_line.length() - 1))
			{
				std::string name = config_line.substr(0, seperate_pos);
				std::string value = config_line.substr(seperate_pos + 1, config_line.length() - seperate_pos - 1);
				if (name == "BinaryRootFolder")
				{
					m_root_folder = config_file_path.parent_path().parent_path() / value;
				}
				else if (name == "AssetFolder")
				{
					m_asset_folder = m_root_folder / value;
				}
				else if (name == "DefaultWorld")
				{
					m_default_world_url = value;
				}
				else if (name == "GlobalRenderingRes")
				{
					m_global_rendering_res_url = value;
				}

			}
		}

	}

	const std::filesystem::path& ConfigManager::GetRootFolder() const { return m_root_folder; }

	const std::filesystem::path& ConfigManager::GetAssetFolder() const { return m_asset_folder; }

	const std::string& ConfigManager::GetDefaultWorldUrl() const { return m_default_world_url; }

	const std::string& ConfigManager::GetGlobalRenderingResUrl() const { return m_global_rendering_res_url; }
	
}