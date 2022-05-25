#pragma once

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
	};
} // namespace ME

