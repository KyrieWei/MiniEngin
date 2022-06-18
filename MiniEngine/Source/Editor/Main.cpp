#include <iostream>

#include "Runtime/Engine.h"
#include "Editor.h"

#define MINIENGINE_XSTR(s) MINIENGINE_STR(s)
#define MINIENGINE_STR(s) #s

int main(int argc, char** argv)
{
	std::filesystem::path executable_path(argv[0]);
	std::filesystem::path config_file_path = executable_path.parent_path().parent_path().parent_path() / "Configs\\MiniEngineEditor.ini";


	ME::MiniEngine* engine = new ME::MiniEngine();

	engine->StartEngine(config_file_path.generic_string());
	engine->Initialize();

	ME::MiniEngineEditor* editor = new ME::MiniEngineEditor();

	editor->Initialize(engine);

	editor->Run();

	editor->Clear();


	engine->Clear();
	engine->ShutdownEngine();

	return 0;
}