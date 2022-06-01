#pragma once
#include <memory>

namespace ME
{
	class WindowSystem;

	struct RHIInitInfo
	{
		std::shared_ptr<WindowSystem> window_system;
	};

	class RHI
	{
	public:
		virtual ~RHI() = 0;
		virtual void Initialize(RHIInitInfo init_info) = 0;
		virtual void PrepareContext() = 0;

	private:

	};

	inline RHI::~RHI() = default;
}

