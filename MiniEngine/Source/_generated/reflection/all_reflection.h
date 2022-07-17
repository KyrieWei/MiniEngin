#pragma once
#include "runtime/core/meta/reflection/reflection.h"
#include "_generated/serializer/all_serializer.h"
#include "_generated\reflection\Object.reflection.gen.h"
#include "_generated\reflection\Vector3.reflection.gen.h"
#include "_generated\reflection\World.reflection.gen.h"
#include "_generated\reflection\Matrix4.reflection.gen.h"
#include "_generated\reflection\Vector2.reflection.gen.h"
#include "_generated\reflection\Quaternion.reflection.gen.h"
#include "_generated\reflection\Vector4.reflection.gen.h"
#include "_generated\reflection\RenderObject.reflection.gen.h"
#include "_generated\reflection\Level.reflection.gen.h"

namespace ME{
namespace Reflection{
    void TypeMetaRegister::Register(){
    TypeWrappersRegister::ComponentDefinitionRes();
    TypeWrappersRegister::ObjectDefinitionRes();
    TypeWrappersRegister::ObjectInstanceRes();
    TypeWrappersRegister::Vector3();
    TypeWrappersRegister::WorldRes();
    TypeWrappersRegister::Matrix4x4_();
    TypeWrappersRegister::Vector2();
    TypeWrappersRegister::Quaternion();
    TypeWrappersRegister::Vector4();
    TypeWrappersRegister::GameObjectMeshDesc();
    TypeWrappersRegister::GameObjectPartDesc();
    TypeWrappersRegister::LevelRes();
    }
}
}

