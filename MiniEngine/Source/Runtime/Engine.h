#pragma once
#include <filesystem>


namespace ME
{
	struct EngineInitParams
	{
		std::filesystem::path m_root_folder;
		std::filesystem::path m_config_file_path;
	};

	class MiniEngine
	{

	public:
		void StartEngine(const EngineInitParams& param);
		void ShutdownEngine();

		void Initialize();
		void Clear();

		void Run();


	};

}  // namespace MiniEngine

