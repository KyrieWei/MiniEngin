#pragma once

#include <functional>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

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

	template<typename T>
	class ReflectionPtr
	{
		template<typename U>
		friend class ReflectionPtr;

	public:
		ReflectionPtr(std::string type_name, T* instance) : m_type_name(type_name), m_instance(instance) {}
		ReflectionPtr() : m_type_name(), m_instance(nullptr) {}

		ReflectionPtr(const ReflectionPtr& dest) : m_type_name(dest.m_type_name), m_instance(dest.m_instance) {}

		template<typename U>
		ReflectionPtr<T>& operator=(const ReflectionPtr<U>& dest)
		{
			if (this == static_cast<void*>(&dest))
			{
				return *this;
			}

			m_type_name = dest.m_type_name;
			m_instance = static_cast<T*>(dest.m_instance);
			return *this;
		}



	private:
		std::string m_type_name{ "" };
		typedef T m_type;
		T* m_instance{ nullptr };
	};

} //namespace MiniEngine