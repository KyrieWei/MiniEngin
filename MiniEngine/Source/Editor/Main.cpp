#include <iostream>

#include "Runtime/Engine.h"
#include "Editor.h"

#define MINIENGINE_XSTR(s) MINIENGINE_STR(s)
#define MINIENGINE_STR(s) #s

int main()
{
	std::filesystem::path mini_engine_root_folder = std::filesystem::path(MINIENGINE_XSTR(MINIENGINE_ROOT_DIR));

	ME::EngineInitParams params;

	params.m_root_folder = mini_engine_root_folder;
	params.m_config_file_path = mini_engine_root_folder / "MiniEngineEditor.ini";

	ME::MiniEngine* engine = new ME::MiniEngine();

	engine->StartEngine(params);
	engine->Initialize();

	ME::MiniEngineEditor* editor = new ME::MiniEngineEditor();

	editor->Initialize(engine);

	editor->Run();

	editor->Clear();


	engine->Clear();
	engine->ShutdownEngine();

	return 0;
}