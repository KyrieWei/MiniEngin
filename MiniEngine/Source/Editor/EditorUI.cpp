#include "EditorUI.h"

#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"

namespace ME
{

	EditorUI::EditorUI()
	{

	}

	void EditorUI::Initialize()
	{

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();

		//// set ui content scale;
		float x_scale, y_scale;
		ImGuiIO& io = ImGui::GetIO();

	}


} // namespace ME