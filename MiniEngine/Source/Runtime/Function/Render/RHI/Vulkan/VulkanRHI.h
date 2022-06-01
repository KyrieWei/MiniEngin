#pragma once
#include "Runtime/Function/Render/RHI.h"

namespace ME
{
	class VulkanRHI final : public RHI
	{
	public:
		// override functions
		virtual ~VulkanRHI() override final;
		virtual void Initialize(RHIInitInfo init_info) override final;
		virtual void PrepareContext() override final;
	};
}

