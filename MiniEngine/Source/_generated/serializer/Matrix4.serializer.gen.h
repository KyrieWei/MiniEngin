#pragma once
#include "Runtime\Core\Math\Matrix4.h"

namespace ME{
    template<>
    PJson PSerializer::Write(const Matrix4x4_& instance);
    template<>
    Matrix4x4_& PSerializer::Read(const PJson& json_context, Matrix4x4_& instance);
}//namespace

