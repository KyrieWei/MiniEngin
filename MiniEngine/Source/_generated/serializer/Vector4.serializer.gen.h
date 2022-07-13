#pragma once
#include "Runtime\Core\Math\Vector4.h"

namespace ME{
    template<>
    PJson PSerializer::Write(const Vector4& instance);
    template<>
    Vector4& PSerializer::Read(const PJson& json_context, Vector4& instance);
}//namespace

