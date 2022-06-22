#include "Engine.h"

#include "Runtime/Core/Base/Macro.h"
#include "Runtime/Function/Render/WindowSystem.h"
#include "Runtime/Function/Render/RenderSystem.h"
#include "Runtime/Function/Global/GlobalContext.h"

namespace ME
{
	const float MiniEngine::k_fps_alpha = 1.f / 100;

	void MiniEngine::StartEngine(const std::string& config_file_path)
	{
		g_runtime_global_context.StartSystems(config_file_path);

		LOG_INFO("Engine Start");
	}

	void MiniEngine::ShutdownEngine()
	{
		LOG_INFO("Engine Shutdown");

		g_runtime_global_context.ShutdownSystems();
	}

	void MiniEngine::Initialize()
	{

	}

	void MiniEngine::Clear()
	{

	}

	void MiniEngine::Run()
	{

	}

	float MiniEngine::CalculateDeltaTime()
	{
		float delta_time;
		{
			using namespace std::chrono;

			steady_clock::time_point tick_time_point = steady_clock::now();
			duration<float> time_span = duration_cast<duration<float>>(tick_time_point - m_last_tick_time_point);
			delta_time = time_span.count();

			m_last_tick_time_point = tick_time_point;
		}

		return delta_time;
	}

	bool MiniEngine::TickOneFrame(float delta_time)
	{
		CalculateFPS(delta_time);

		// single thread
		// exchange data between logic and render contexts
		g_runtime_global_context.m_render_system->SwapLogicRenderData();

		RenderTick();

		g_runtime_global_context.m_window_system->PollEvents();

		const bool should_window_close = g_runtime_global_context.m_window_system->ShouldClose();
		return !should_window_close;
	}


	
	void MiniEngine::CalculateFPS(float delta_time)
	{
		m_frame_count++;
		if (m_frame_count == 1)
		{
			m_average_duration = delta_time;
		}
		else
		{
			m_average_duration = m_average_duration * (1 - k_fps_alpha) + delta_time * k_fps_alpha;
		}

		m_fps = static_cast<int>(1.f / m_average_duration);
	}

	bool MiniEngine::RenderTick()
	{
		g_runtime_global_context.m_render_system->Tick();
		return true;
	}
}