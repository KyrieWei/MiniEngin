#pragma once

namespace ME
{
#define META(...)
#define CLASS(class_name, ...) class class_name
#define STRUCT(struct_name, ...) struct struct_name

#define REFLECTION_BODY(class_name) \
	friend class Reflection::TypeFieldReflectionOperator::Type##class_name##Operator; \
	friend class PSerializer;

#define REFLECTION_TYPE(class_name) \
	namespace Reflection \
	{ \
		namespace TypeFieldReflectionOperator \
		{ \
			class Type##class_name##Operator; \
		} \
	};


} //namespace MiniEngine