#pragma once

#include <filesystem>

namespace ME
{
	struct EngineInitParams;

	class ConfigManager
	{
	public:
		void Initialize(const std::filesystem::path& config_file_path);

		const std::filesystem::path& GetRootFolder() const;
		const std::filesystem::path& GetAssetFolder() const;

		const std::string& GetDefaultWorldUrl() const;
		const std::string& GetGlobalRenderingResUrl() const;

	private:
		std::filesystem::path m_root_folder;
		std::filesystem::path m_asset_folder;

		std::string m_default_world_url;
		std::string m_global_rendering_res_url;

	};
}



