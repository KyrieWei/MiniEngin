#include "RenderSwapContext.h"

namespace ME
{
	void GameObjectResourceDesc::Add(GameObjectDesc desc) { m_game_object_descs.push_back(desc); }

	bool GameObjectResourceDesc::IsEmpty() const { return m_game_object_descs.empty(); }

	GameObjectDesc GameObjectResourceDesc::GetNextProcessObject()
	{
		if (!m_game_object_descs.empty())
		{
			return m_game_object_descs.front();
		}
		else
		{
			return GameObjectDesc();
		}
	}

	void GameObjectResourceDesc::PopProcessObject() { m_game_object_descs.pop_front(); }


	RenderSwapData& RenderSwapContext::GetLogicSwapData() { return m_swap_data[m_logic_swap_data_index]; }

	RenderSwapData& RenderSwapContext::GetRenderSwapData() { return m_swap_data[m_render_swap_data_index]; }

	void RenderSwapContext::SwapLogicRenderData()
	{
		if (IsReadyToSwap())
		{
			Swap();
		}
	}

	bool RenderSwapContext::IsReadyToSwap() const
	{
		return !(m_swap_data[m_render_swap_data_index].m_game_object_resource_desc.has_value());
	}

	void RenderSwapContext::ResetLevelResourceSwapData() {}

	void RenderSwapContext::ResetGameObjectResourceSwapData() 
	{
		m_swap_data[m_render_swap_data_index].m_game_object_resource_desc.reset();
	}

	void RenderSwapContext::ResetGameObjectToDelete() 
	{
		//m_swap_data[m_render_swap_data_index].m_game_object_to_delete.reset();
	}

	void RenderSwapContext::ResetCameraSwapData(){}

	void RenderSwapContext::Swap()
	{
		ResetLevelResourceSwapData();
		ResetGameObjectResourceSwapData();
		ResetGameObjectToDelete();
		ResetCameraSwapData();
		std::swap(m_logic_swap_data_index, m_render_swap_data_index);
	}
}
