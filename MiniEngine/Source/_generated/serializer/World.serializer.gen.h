#pragma once
#include "Runtime\Resource\ResType\Common\World.h"

namespace ME{
    template<>
    PJson PSerializer::Write(const WorldRes& instance);
    template<>
    WorldRes& PSerializer::Read(const PJson& json_context, WorldRes& instance);
}//namespace

