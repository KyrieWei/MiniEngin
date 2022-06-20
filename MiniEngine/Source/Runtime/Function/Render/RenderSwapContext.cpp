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
}
