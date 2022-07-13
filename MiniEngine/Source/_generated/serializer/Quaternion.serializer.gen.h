#pragma once
#include "Runtime\Core\Math\Quaternion.h"

namespace ME{
    template<>
    PJson PSerializer::Write(const Quaternion& instance);
    template<>
    Quaternion& PSerializer::Read(const PJson& json_context, Quaternion& instance);
}//namespace

