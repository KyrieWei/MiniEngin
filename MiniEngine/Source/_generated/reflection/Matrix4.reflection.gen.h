#pragma once
#include "Runtime\Core\Math\Matrix4.h"

namespace ME{
    class Matrix4x4_;
namespace Reflection{
namespace TypeFieldReflectionOparator{
    class TypeMatrix4x4_Operator{
    public:
        static const char* GetClassName(){ return "Matrix4x4_";}
        static void* ConstructorWithJson(const PJson& json_context){
            Matrix4x4_* ret_instance= new Matrix4x4_;
            PSerializer::Read(json_context, *ret_instance);
            return ret_instance;
        }
        static PJson WriteByName(void* instance){
            return PSerializer::Write(*(Matrix4x4_*)instance);
        }
        // base class
        static int GetMatrix4x4_BaseClassReflectionInstanceList(ReflectionInstance* &out_list, void* instance){
            int count = 0;
            
            return count;
        }
        // fields
        
    };
}//namespace TypeFieldReflectionOparator


    void TypeWrapperRegister_Matrix4x4_(){
        
        
        
        ClassFunctionTuple* f_class_function_tuple_Matrix4x4_=new ClassFunctionTuple(
            &TypeFieldReflectionOparator::TypeMatrix4x4_Operator::GetMatrix4x4_BaseClassReflectionInstanceList,
            &TypeFieldReflectionOparator::TypeMatrix4x4_Operator::ConstructorWithJson,
            &TypeFieldReflectionOparator::TypeMatrix4x4_Operator::WriteByName);
        REGISTER_BASE_CLASS_TO_MAP("Matrix4x4_", f_class_function_tuple_Matrix4x4_);
    }
namespace TypeWrappersRegister{
        void Matrix4x4_(){ TypeWrapperRegister_Matrix4x4_();}
}//namespace TypeWrappersRegister

}//namespace Reflection
}//namespace ME

