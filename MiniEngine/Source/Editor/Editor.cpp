#include "Editor.h"
#include "Runtime/Engine.h"
#include "Runtime/Function/Global/GlobalContext.h"
#include "Editor/EditorUI.h"
#include <cassert>

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
		assert(engine_runtime);

		m_engine_runtime = engine_runtime;

		m_editor_ui = std::make_shared<EditorUI>();

		WindowUIInitInfo ui_init_info = { g_runtime_global_context.m_window_system };
		m_editor_ui->Initialize(ui_init_info);
	}

	void MiniEngineEditor::Clear()
	{

	}

	void MiniEngineEditor::Run()
	{
		assert(m_engine_runtime);
		assert(m_editor_ui);
		float delta_time;
		while (true)
		{
			delta_time = m_engine_runtime->CalculateDeltaTime();
			if (!m_engine_runtime->TickOneFrame(delta_time))
				return;
		}
	}
}