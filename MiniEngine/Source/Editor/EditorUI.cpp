#include "EditorUI.h"

#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"

#include "Runtime/Function/Render/WindowSystem.h"

namespace ME
{

	EditorUI::EditorUI()
	{

	}

	void EditorUI::ShowEditorUI()
	{
		bool editor_menu_window_open		= true;
		bool asset_window_open				= true;
		bool game_engine_window_open		= true;
		bool file_content_window_open		= true;
		bool detail_window_open				= true;
		bool scene_lights_window_open		= true;
		bool scene_lights_data_window_open	= true;

		ShowEditorMenu(&editor_menu_window_open);
		ShowEditroWorldObjectsWindow(&asset_window_open);
		ShowEditorGameWindow(&game_engine_window_open);
		ShowEditorFileContentWindow(&file_content_window_open);
		ShowEditorDetailWindow(&detail_window_open);
	}

	void EditorUI::ShowEditorMenu(bool* bOpen)
	{
		ImGuiDockNodeFlags dock_flags = ImGuiDockNodeFlags_DockSpace;
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoTitleBar |
			ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize |
			ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBackground |
			ImGuiConfigFlags_NoMouseCursorChange | ImGuiWindowFlags_NoBringToFrontOnFocus;

		const ImGuiViewport* main_viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(main_viewport->WorkPos, ImGuiCond_Always);
		std::array<int, 2> window_size = { 1280, 722 };
		ImGui::SetNextWindowSize(ImVec2((float)window_size[0], (float)window_size[1]), ImGuiCond_Always);

		ImGui::SetNextWindowViewport(main_viewport->ID);

		ImGui::Begin("Editor Menu", bOpen, window_flags);

		//ImGuiID main_docking_id = ImGui::GetID("Main Docking");
		//if (ImGui::DockBuilderGetNode(main_docking_id) == nullptr)
		//{
		//	ImGui::DockBuilderRemoveNode(main_docking_id);

		//	ImGui::DockBuilderAddNode(main_docking_id, dock_flags);
		//	ImGui::DockBuilderSetNodePos(main_docking_id,
		//		ImVec2(main_viewport->WorkPos.x, main_viewport->WorkPos.y + 18.0f));
		//	ImGui::DockBuilderSetNodeSize(main_docking_id,
		//		ImVec2((float)window_size[0], (float)window_size[1] - 18.0f));

		//	ImGuiID center = main_docking_id;
		//	ImGuiID left;
		//	ImGuiID right = ImGui::DockBuilderSplitNode(center, ImGuiDir_Right, 0.25f, nullptr, &left);

		//	ImGuiID left_other;
		//	ImGuiID left_file_content = ImGui::DockBuilderSplitNode(left, ImGuiDir_Down, 0.30f, nullptr, &left_other);

		//	ImGuiID left_game_engine;
		//	ImGuiID left_asset =
		//		ImGui::DockBuilderSplitNode(left_other, ImGuiDir_Left, 0.30f, nullptr, &left_game_engine);

		//	ImGui::DockBuilderDockWindow("World Objects", left_asset);
		//	ImGui::DockBuilderDockWindow("Components Details", right);
		//	ImGui::DockBuilderDockWindow("File Content", left_file_content);
		//	ImGui::DockBuilderDockWindow("Game Engine", left_game_engine);

		//	ImGui::DockBuilderFinish(main_docking_id);
		//}

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("Menu"))
			{
				if (ImGui::MenuItem("Reload Current Level"))
				{
					//g_runtime_global_context.m_world_manager->reloadCurrentLevel();
					//g_runtime_global_context.m_render_system->clearForLevelReloading();
					//g_editor_global_context.m_scene_manager->onGObjectSelected(k_invalid_gobject_id);
				}
				if (ImGui::MenuItem("Save Current Level"))
				{
					//g_runtime_global_context.m_world_manager->saveCurrentLevel();
				}
				if (ImGui::MenuItem("Exit"))
				{
					//g_editor_global_context.m_engine_runtime->shutdownEngine();
					exit(0);
				}
				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}

		ImGui::End();
	}

	void EditorUI::ShowEditroWorldObjectsWindow(bool* bOpen)
	{

	}

	void EditorUI::ShowEditorGameWindow(bool* bOpen)
	{
	
	}
	
	void EditorUI::ShowEditorFileContentWindow(bool* bOpen)
	{

	}

	void EditorUI::ShowEditorDetailWindow(bool* bOpen)
	{
		
	}

	inline void WindowContentScaleUpdate(float scale)
	{
#if defined(__GNUC__) && defined(__MACH__)
		float font_scale = fmaxf(1.0f, scale);
		ImGui::GetIO().FontGlobalScale = 1.0f / font_scale;
#endif
	}

	inline void WindowContentScaleCallback(GLFWwindow* window, float x_scale, float y_scale)
	{
		WindowContentScaleUpdate(fmaxf(x_scale, y_scale));
	}

	void EditorUI::Initialize(WindowUIInitInfo init_info)
	{

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();

		//// set ui content scale;
		float x_scale, y_scale;
		glfwGetWindowContentScale(init_info.window_system->GetWindow(), &x_scale, &y_scale);
		float content_scale = fmaxf(1.0f, fmaxf(x_scale, y_scale));
		WindowContentScaleUpdate(content_scale);
		glfwSetWindowContentScaleCallback(init_info.window_system->GetWindow(), WindowContentScaleCallback);
		
		ImGuiIO& io = ImGui::GetIO();
		io.ConfigWindowsMoveFromTitleBarOnly = true;

		
		
		ImGuiStyle& style = ImGui::GetStyle();
		style.WindowPadding = ImVec2(1.0, 0);
		style.FramePadding = ImVec2(14.0, 2.0);
		style.ChildBorderSize = 0.0f;
		style.FrameRounding = 5.0f;
		style.FrameBorderSize = 1.5f;

		SetUIColorStyle();


	}

	void EditorUI::SetUIColorStyle()
	{
		ImGuiStyle* style = &ImGui::GetStyle();
		ImVec4* colors = style->Colors;

		colors[ImGuiCol_Text] = ImVec4(0.4745f, 0.4745f, 0.4745f, 1.00f);
		colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
		colors[ImGuiCol_WindowBg] = ImVec4(0.0078f, 0.0078f, 0.0078f, 1.00f);
		colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
		colors[ImGuiCol_Border] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
		colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		colors[ImGuiCol_FrameBg] = ImVec4(0.047f, 0.047f, 0.047f, 0.5411f);
		colors[ImGuiCol_FrameBgHovered] = ImVec4(0.196f, 0.196f, 0.196f, 0.40f);
		colors[ImGuiCol_FrameBgActive] = ImVec4(0.294f, 0.294f, 0.294f, 0.67f);
		colors[ImGuiCol_TitleBg] = ImVec4(0.0039f, 0.0039f, 0.0039f, 1.00f);
		colors[ImGuiCol_TitleBgActive] = ImVec4(0.0039f, 0.0039f, 0.0039f, 1.00f);
		colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.50f);
		colors[ImGuiCol_MenuBarBg] = ImVec4(0.0f, 0.0f, 0.0f, 1.00f);
		colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
		colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
		colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
		colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
		colors[ImGuiCol_CheckMark] = ImVec4(93.0f / 255.0f, 10.0f / 255.0f, 66.0f / 255.0f, 1.00f);
		colors[ImGuiCol_SliderGrab] = colors[ImGuiCol_CheckMark];
		colors[ImGuiCol_SliderGrabActive] = ImVec4(0.3647f, 0.0392f, 0.2588f, 0.50f);
		colors[ImGuiCol_Button] = ImVec4(0.0117f, 0.0117f, 0.0117f, 1.00f);
		colors[ImGuiCol_ButtonHovered] = ImVec4(0.0235f, 0.0235f, 0.0235f, 1.00f);
		colors[ImGuiCol_ButtonActive] = ImVec4(0.0353f, 0.0196f, 0.0235f, 1.00f);
		colors[ImGuiCol_Header] = ImVec4(0.1137f, 0.0235f, 0.0745f, 0.588f);
		colors[ImGuiCol_HeaderHovered] = ImVec4(5.0f / 255.0f, 5.0f / 255.0f, 5.0f / 255.0f, 1.00f);
		colors[ImGuiCol_HeaderActive] = ImVec4(0.0f, 0.0f, 0.0f, 1.00f);
		colors[ImGuiCol_Separator] = ImVec4(0.0f, 0.0f, 0.0f, 0.50f);
		colors[ImGuiCol_SeparatorHovered] = ImVec4(45.0f / 255.0f, 7.0f / 255.0f, 26.0f / 255.0f, 1.00f);
		colors[ImGuiCol_SeparatorActive] = ImVec4(45.0f / 255.0f, 7.0f / 255.0f, 26.0f / 255.0f, 1.00f);
		colors[ImGuiCol_ResizeGrip] = ImVec4(0.26f, 0.59f, 0.98f, 0.20f);
		colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
		colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
		colors[ImGuiCol_Tab] = ImVec4(6.0f / 255.0f, 6.0f / 255.0f, 8.0f / 255.0f, 1.00f);
		colors[ImGuiCol_TabHovered] = ImVec4(45.0f / 255.0f, 7.0f / 255.0f, 26.0f / 255.0f, 150.0f / 255.0f);
		colors[ImGuiCol_TabActive] = ImVec4(47.0f / 255.0f, 6.0f / 255.0f, 29.0f / 255.0f, 1.0f);
		colors[ImGuiCol_TabUnfocused] = ImVec4(45.0f / 255.0f, 7.0f / 255.0f, 26.0f / 255.0f, 25.0f / 255.0f);
		colors[ImGuiCol_TabUnfocusedActive] = ImVec4(6.0f / 255.0f, 6.0f / 255.0f, 8.0f / 255.0f, 200.0f / 255.0f);
		colors[ImGuiCol_DockingPreview] = ImVec4(47.0f / 255.0f, 6.0f / 255.0f, 29.0f / 255.0f, 0.7f);
		colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.20f, 0.20f, 0.20f, 0.00f);
		colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
		colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
		colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
		colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
		colors[ImGuiCol_TableHeaderBg] = ImVec4(0.0f, 0.0f, 0.0f, 1.00f);
		colors[ImGuiCol_TableBorderStrong] = ImVec4(2.0f / 255.0f, 2.0f / 255.0f, 2.0f / 255.0f, 1.0f);
		colors[ImGuiCol_TableBorderLight] = ImVec4(0.23f, 0.23f, 0.25f, 1.00f);
		colors[ImGuiCol_TableRowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
		colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
		colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
		colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
		colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
		colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
		colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
	}

	void EditorUI::PreRender() { ShowEditorUI(); }
} // namespace ME