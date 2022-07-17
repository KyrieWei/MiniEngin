#pragma once
#include "Runtime\Resource\ResType\Common\Level.h"

namespace ME{
    class LevelRes;
namespace Reflection{
namespace TypeFieldReflectionOparator{
    class TypeLevelResOperator{
    public:
        static const char* GetClassName(){ return "LevelRes";}
        static void* ConstructorWithJson(const PJson& json_context){
            LevelRes* ret_instance= new LevelRes;
            PSerializer::Read(json_context, *ret_instance);
            return ret_instance;
        }
        static PJson WriteByName(void* instance){
            return PSerializer::Write(*(LevelRes*)instance);
        }
        // base class
        static int GetLevelResBaseClassReflectionInstanceList(ReflectionInstance* &out_list, void* instance){
            int count = 0;
            
            return count;
        }
        // fields
        
    };
}//namespace TypeFieldReflectionOparator
namespace ArrayReflectionOperator{
#ifndef ArraystdSSvectorLObjectInstanceResROperatorMACRO
#define ArraystdSSvectorLObjectInstanceResROperatorMACRO
    class ArraystdSSvectorLObjectInstanceResROperator{
        public:
            static const char* GetArrayTypeName(){ return "std::vector<ObjectInstanceRes>";}
            static const char* GetElementTypeName(){ return "ObjectInstanceRes";}
            static int GetSize(void* instance){
                //todo: should check validation
                return static_cast<int>(static_cast<std::vector<ObjectInstanceRes>*>(instance)->size());
            }
            static void* Get(int index,void* instance){
                //todo: should check validation
                return static_cast<void*>(&((*static_cast<std::vector<ObjectInstanceRes>*>(instance))[index]));
            }
            static void Set(int index, void* instance, void* element_value){
                //todo: should check validation
                (*static_cast<std::vector<ObjectInstanceRes>*>(instance))[index] = *static_cast<ObjectInstanceRes*>(element_value);
            }
    };
#endif //ArraystdSSvectorLObjectInstanceResROperator
}//namespace ArrayReflectionOperator

    void TypeWrapperRegister_LevelRes(){
        
        
        ArrayFunctionTuple* f_array_tuple_stdSSvectorLObjectInstanceResR = new  ArrayFunctionTuple(
            &ArrayReflectionOperator::ArraystdSSvectorLObjectInstanceResROperator::Set,
            &ArrayReflectionOperator::ArraystdSSvectorLObjectInstanceResROperator::Get,
            &ArrayReflectionOperator::ArraystdSSvectorLObjectInstanceResROperator::GetSize,
            &ArrayReflectionOperator::ArraystdSSvectorLObjectInstanceResROperator::GetArrayTypeName,
            &ArrayReflectionOperator::ArraystdSSvectorLObjectInstanceResROperator::GetElementTypeName);
        REGISTER_ARRAY_TO_MAP("std::vector<ObjectInstanceRes>", f_array_tuple_stdSSvectorLObjectInstanceResR);
        ClassFunctionTuple* f_class_function_tuple_LevelRes=new ClassFunctionTuple(
            &TypeFieldReflectionOparator::TypeLevelResOperator::GetLevelResBaseClassReflectionInstanceList,
            &TypeFieldReflectionOparator::TypeLevelResOperator::ConstructorWithJson,
            &TypeFieldReflectionOparator::TypeLevelResOperator::WriteByName);
        REGISTER_BASE_CLASS_TO_MAP("LevelRes", f_class_function_tuple_LevelRes);
    }
namespace TypeWrappersRegister{
        void LevelRes(){ TypeWrapperRegister_LevelRes();}
}//namespace TypeWrappersRegister

}//namespace Reflection
}//namespace ME

