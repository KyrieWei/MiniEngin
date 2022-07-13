#pragma once
#include "Runtime\Resource\ResType\Common\Level.h"

namespace ME{
    template<>
    PJson PSerializer::Write(const LevelRes& instance);
    template<>
    LevelRes& PSerializer::Read(const PJson& json_context, LevelRes& instance);
}//namespace

