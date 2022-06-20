#pragma once

#include <atomic>
#include <limits>

namespace ME
{
	using GObjectID = std::size_t;

	constexpr GObjectID k_invalid_gobject_id = std::numeric_limits<std::size_t>::max();

	class ObjectIDAllocator
	{
	public:
		static GObjectID Alloc();

	private:
		static std::atomic<GObjectID> m_next_id;
	};
}



