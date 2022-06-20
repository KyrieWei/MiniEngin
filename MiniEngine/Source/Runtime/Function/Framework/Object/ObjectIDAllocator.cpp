#include "ObjectIDAllocator.h"
#include "Runtime/Core/Base/Macro.h"

namespace ME
{
	std::atomic<GObjectID> ObjectIDAllocator::m_next_id{ 0 };

	GObjectID ObjectIDAllocator::Alloc()
	{
		std::atomic<GObjectID> new_object_ret = m_next_id.load();

		m_next_id++;

		if (m_next_id >= k_invalid_gobject_id)
		{
			LOG_FATAL("GObject ID overflow");
		}

		return new_object_ret;
	}
}