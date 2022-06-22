#pragma once

#include "Runtime/Function/Render/RenderObject.h"

#include <cstdint>
#include <string>
#include <deque>
#include <optional>

namespace ME
{
	struct LevelIBLResourceDesc
	{
		std::string	m_brdf_map;
	};

	struct LevelColorGradingResourceDesc
	{
		std::string m_color_grading_map;
	};

	struct LevelResourceDesc
	{
		LevelIBLResourceDesc			m_ibl_resource_desc;
		LevelColorGradingResourceDesc	m_color_grading_resource_desc;
	};

	struct GameObjectResourceDesc
	{
		std::deque<GameObjectDesc> m_game_object_descs;

		void Add(GameObjectDesc desc);
		bool IsEmpty() const;
		GameObjectDesc GetNextProcessObject();
		void PopProcessObject();
	};

	struct RenderSwapData
	{
		std::optional<GameObjectResourceDesc> m_game_object_resource_desc;
	};

	enum SwapDataType : uint8_t
	{
		LogicSwapDataType = 0,
		RenderSwapDataType,
		SwapDataTypeCount
	};

	class RenderSwapContext
	{
	public:
		RenderSwapData& GetLogicSwapData();
		RenderSwapData& GetRenderSwapData();

		void SwapLogicRenderData();
		void ResetLevelResourceSwapData();
		void ResetGameObjectResourceSwapData();
		void ResetGameObjectToDelete();
		void ResetCameraSwapData();

	private:
		uint8_t m_logic_swap_data_index{ LogicSwapDataType };
		uint8_t m_render_swap_data_index{ RenderSwapDataType };
		RenderSwapData m_swap_data[SwapDataTypeCount];

		bool IsReadyToSwap() const;
		void Swap();
	};
}

