#pragma once

#include "Runtime/Function/UI/WindowUI.h"

namespace ME
{
	class MiniEngineEditor;
	
	class EditorUI : public WindowUI
	{
	public:
		EditorUI();

	private:
		void ShowEditorUI();
		void ShowEditorMenu(bool* bOpen);
		void ShowEditroWorldObjectsWindow(bool* bOpen);
		void ShowEditorFileContentWindow(bool* bOpen);
		void ShowEditorGameWindow(bool* bOpen);
		void ShowEditorDetailWindow(bool* bOpen);

		void SetUIColorStyle();

	public:
		virtual void Initialize(WindowUIInitInfo init_info) override final;
		//virtual void PreRender() override final;

		
	};
}

