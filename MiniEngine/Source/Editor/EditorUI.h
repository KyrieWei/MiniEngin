#pragma once

#include "Runtime/Function/UI/WindowUI.h"

namespace ME
{
	class MiniEngineEditor;
	
	class EditorUI : public WindowUI
	{
	public:
		EditorUI();

	public:
		virtual void Initialize() override final;
		//virtual void PreRender() override final;
	};
}

