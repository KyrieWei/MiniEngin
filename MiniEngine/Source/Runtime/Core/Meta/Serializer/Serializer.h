#pragma once
#include "Runtime/Core/Meta/json.h"
#include "Runtime/Core/Meta/Reflection/Reflection.h"

#include <cassert>

namespace ME
{
	template<typename...>
	inline constexpr bool always_false = false;

	class PSerializer
	{
	public:
		template<typename T>
		static PJson WritePointer(T* instance)
		{
			return PJson::object{ {"$TypeName", PJson{"*"}}, {"$context", PSerializer::Write(*instance)} };
		}

		template<typename T>
		static T*& ReadPointer(const PJson& json_context, T*& instance)
		{
			assert(instance == nullptr);
			std::string type_name = json_context["$TypeName"].string_value();
			assert(!type_name.empty());
			if ('*' == type_name[0])
			{
				instance = new T;
				read(json_context["$context"], *instance);
			}
			else
			{
				//instance = static_cast<T*>(Reflection::TypeMeta::)
			}

			return instance;
		}

		template<typename T>
		static PJson Write(const Reflection::ReflectionPtr<T>& instance)
		{
			T* instance_ptr = static_cast<T*>(instance.operator->());
			std::string type_name = instance.GetTypeName();
			return PJson::object{ {"$TypeName", PJson(type_name)}
								  /*{"$context", Reflection::TypeMeta::WriteByName(type_name, instance_ptr)}*/};
		}

		template<typename T>
		static T*& Read(const PJson& json_context, Reflection::ReflectionPtr<T>& instance)
		{
			std::string type_name = json_context["$TypeName"].string_value();
			instance.SetTypeName(type_name);
			return ReadPointer(json_context, instance.GetPtrReference());
		}

		template<typename T>
		static PJson Write(const T& instance)
		{
			if constexpr (std::is_pointer<T>::value)
			{
				return WritePointer((T)instance);
			}
			else
			{
				static_assert(always_false<T>, "PSerializer::write<T> has not been implemented yet!");
				return PJson();
			}
		}

		template<typename T>
		static T& Read(const PJson& json_context, T& instance)
		{
			if constexpr (std::is_pointer<T>::value)
			{
				return ReadPointer(json_context, instance);
			}
			else
			{
				static_assert(always_false<T>, "PSerializer::Read<T> has not been implemented yet!");
				return instance;
			}
		}
		
	};

	// implementation of base types
	template<>
	PJson PSerializer::Write(const char& instance);
	template<>
	char& PSerializer::Read(const PJson& json_context, char& instance);

	template<>
	PJson PSerializer::Write(const int& instance);
	template<>
	int& PSerializer::Read(const PJson& json_context, int& instance);

	template<>
	PJson PSerializer::Write(const unsigned int& instance);
	template<>
	unsigned int& PSerializer::Read(const PJson& json_context, unsigned int& instance);

	template<>
	PJson PSerializer::Write(const float& instance);
	template<>
	float& PSerializer::Read(const PJson& json_context, float& instance);

	template<>
	PJson PSerializer::Write(const double& instance);
	template<>
	double& PSerializer::Read(const PJson& json_context, double& instance);

	template<>
	PJson PSerializer::Write(const bool& instance);
	template<>
	bool& PSerializer::Read(const PJson& json_context, bool& instance);

	template<>
	PJson PSerializer::Write(const std::string& instance);
	template<>
	std::string& PSerializer::Read(const PJson& json_context, std::string& instance);

}
