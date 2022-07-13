#pragma once
#include "Runtime\Core\Math\Vector4.h"

namespace ME{
    class Vector4;
namespace Reflection{
namespace TypeFieldReflectionOparator{
    class TypeVector4Operator{
    public:
        static const char* GetClassName(){ return "Vector4";}
        static void* ConstructorWithJson(const PJson& json_context){
            Vector4* ret_instance= new Vector4;
            PSerializer::Read(json_context, *ret_instance);
            return ret_instance;
        }
        static PJson WriteByName(void* instance){
            return PSerializer::Write(*(Vector4*)instance);
        }
        // base class
        static int GetVector4BaseClassReflectionInstanceList(ReflectionInstance* &out_list, void* instance){
            int count = 0;
            
            return count;
        }
        // fields
        
    };
}//namespace TypeFieldReflectionOparator


    void TypeWrapperRegister_Vector4(){
        
        
        
        ClassFunctionTuple* f_class_function_tuple_Vector4=new ClassFunctionTuple(
            &TypeFieldReflectionOparator::TypeVector4Operator::getVector4BaseClassReflectionInstanceList,
            &TypeFieldReflectionOparator::TypeVector4Operator::constructorWithJson,
            &TypeFieldReflectionOparator::TypeVector4Operator::writeByName);
        REGISTER_BASE_CLASS_TO_MAP("Vector4", f_class_function_tuple_Vector4);
    }
namespace TypeWrappersRegister{
        void Vector4(){ TypeWrapperRegister_Vector4();}
}//namespace TypeWrappersRegister

}//namespace Reflection
}//namespace ME

