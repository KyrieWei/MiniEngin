#pragma once
#include "Runtime\Core\Math\Vector2.h"

namespace ME{
    template<>
    PJson PSerializer::Write(const Vector2& instance);
    template<>
    Vector2& PSerializer::Read(const PJson& json_context, Vector2& instance);
}//namespace

