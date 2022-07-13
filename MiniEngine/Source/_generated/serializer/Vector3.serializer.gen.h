#pragma once
#include "Runtime\Core\Math\Vector3.h"

namespace ME{
    template<>
    PJson PSerializer::Write(const Vector3& instance);
    template<>
    Vector3& PSerializer::Read(const PJson& json_context, Vector3& instance);
}//namespace

