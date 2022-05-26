#include "Editor.h"
#include "Editor/EditorUI.h"

namespace ME
{
	MiniEngineEditor::MiniEngineEditor()
	{

	}

	MiniEngineEditor::~MiniEngineEditor()
	{

	}

	void MiniEngineEditor::Initialize(MiniEngine* engine_runtime)
	{
		m_editor_ui = std::make_shared<EditorUI>();
		m_editor_ui->Initialize();
	}

	void MiniEngineEditor::Clear()
	{

	}

	void MiniEngineEditor::Run()
	{

	}
}