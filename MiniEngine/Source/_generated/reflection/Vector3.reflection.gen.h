#pragma once
#include "Runtime\Core\Math\Vector3.h"

namespace ME{
    class Vector3;
namespace Reflection{
namespace TypeFieldReflectionOparator{
    class TypeVector3Operator{
    public:
        static const char* GetClassName(){ return "Vector3";}
        static void* ConstructorWithJson(const PJson& json_context){
            Vector3* ret_instance= new Vector3;
            PSerializer::Read(json_context, *ret_instance);
            return ret_instance;
        }
        static PJson WriteByName(void* instance){
            return PSerializer::Write(*(Vector3*)instance);
        }
        // base class
        static int GetVector3BaseClassReflectionInstanceList(ReflectionInstance* &out_list, void* instance){
            int count = 0;
            
            return count;
        }
        // fields
        
    };
}//namespace TypeFieldReflectionOparator


    void TypeWrapperRegister_Vector3(){
        
        
        
        ClassFunctionTuple* f_class_function_tuple_Vector3=new ClassFunctionTuple(
            &TypeFieldReflectionOparator::TypeVector3Operator::getVector3BaseClassReflectionInstanceList,
            &TypeFieldReflectionOparator::TypeVector3Operator::constructorWithJson,
            &TypeFieldReflectionOparator::TypeVector3Operator::writeByName);
        REGISTER_BASE_CLASS_TO_MAP("Vector3", f_class_function_tuple_Vector3);
    }
namespace TypeWrappersRegister{
        void Vector3(){ TypeWrapperRegister_Vector3();}
}//namespace TypeWrappersRegister

}//namespace Reflection
}//namespace ME

