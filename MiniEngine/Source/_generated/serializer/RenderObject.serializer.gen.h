#pragma once
#include "Runtime\Function\Render\RenderObject.h"

namespace ME{
    template<>
    PJson PSerializer::Write(const GameObjectMeshDesc& instance);
    template<>
    GameObjectMeshDesc& PSerializer::Read(const PJson& json_context, GameObjectMeshDesc& instance);
    template<>
    PJson PSerializer::Write(const GameObjectPartDesc& instance);
    template<>
    GameObjectPartDesc& PSerializer::Read(const PJson& json_context, GameObjectPartDesc& instance);
}//namespace

