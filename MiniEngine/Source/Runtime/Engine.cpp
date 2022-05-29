#include "Engine.h"

#include "Runtime/Core/Base/Macro.h"
#include "Runtime/Function/Render/WindowSystem.h"
#include "Runtime/Function/Global/GlobalContext.h"

namespace ME
{
	void MiniEngine::StartEngine(const EngineInitParams& param)
	{
		m_init_params = param;

		g_runtime_global_context.StartSystems(param);

		LOG_INFO("Engine Start");
	}

	void MiniEngine::ShutdownEngine()
	{
		LOG_INFO("Engine Shutdown");
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

		RenderTick();

		const bool should_window_close = g_runtime_global_context.m_window_system->ShouldClose();
		return !should_window_close;
	}



	void MiniEngine::CalculateFPS(float delta_time)
	{

	}

	bool MiniEngine::RenderTick()
	{
		//g_runtime_global_contex
	}
}