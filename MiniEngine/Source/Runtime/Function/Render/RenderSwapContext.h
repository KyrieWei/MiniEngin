#pragma once

#include <string>

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


}

