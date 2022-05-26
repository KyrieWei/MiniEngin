#pragma once

#include <memory>

namespace ME
{
	class EditorUI;
	class MiniEngine;

	class MiniEngineEditor
	{
		friend class EditorUI;

	public:
		MiniEngineEditor();
		virtual ~MiniEngineEditor();

		void Initialize(MiniEngine* engine_runtime);

		void Clear();

		void Run();

	protected:
		std::shared_ptr<EditorUI> m_editor_ui;
		MiniEngine* m_engine_runtime{ nullptr };
	};
} // namespace ME

