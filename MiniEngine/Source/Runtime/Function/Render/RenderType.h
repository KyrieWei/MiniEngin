#pragma once
#include <cstdint>

enum class RENDER_PIPELINE_TYPE : uint8_t
{
	FORWARD_PIPELINE = 0,
	DEFERRED_PIPELINE,
	PIPELINE_TYPE_COUNT
};