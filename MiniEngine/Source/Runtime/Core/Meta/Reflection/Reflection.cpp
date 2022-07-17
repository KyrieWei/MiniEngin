#include "Reflection.h"
#include <cstring>
#include <map>

namespace ME
{
	namespace Reflection
	{
		const char* k_unknown_type = "UnknownType";
		const char* k_unknown = "Unknown";

		static std::map<std::string, ClassFunctionTuple*> m_class_map;
		static std::multimap<std::string, FieldFunctionTuple*> m_field_map;
		static std::map<std::string, ArrayFunctionTuple*> m_array_map;

		void TypeMetaRegisterInterface::RegisterToFieldMap(const char* name, FieldFunctionTuple* value)
		{
			m_field_map.insert(std::make_pair(name, value));
		}

		void TypeMetaRegisterInterface::RegisterToArrayMap(const char* name, ArrayFunctionTuple* value)
		{
			if (m_array_map.find(name) == m_array_map.end())
			{
				m_array_map.insert(std::make_pair(name, value));
			}
			else
			{
				delete value;
			}
		}

		void TypeMetaRegisterInterface::RegisterToClassMap(const char* name, ClassFunctionTuple* value)
		{
			if (m_class_map.find(name) == m_class_map.end())
			{
				m_class_map.insert(std::make_pair(name, value));
			}
			else
			{
				delete value;
			}
		}

		void TypeMetaRegisterInterface::UnregisterAll()
		{
			for (const auto& iter : m_field_map)
			{
				delete iter.second;
			}
			m_field_map.clear();
			for (const auto& iter : m_class_map)
			{
				delete iter.second;
			}
			m_class_map.clear();
			for (const auto& iter : m_array_map)
			{
				delete iter.second;
			}
			m_array_map.clear();
		}

		TypeMeta::TypeMeta(std::string type_name) : m_type_name(type_name)
		{
			m_is_valid = false;
			m_fields.clear();

			auto fields_iter = m_field_map.equal_range(type_name);
			while (fields_iter.first != fields_iter.second)
			{
				FieldAccessor f_field(fields_iter.first->second);
				m_fields.emplace_back(f_field);
				m_is_valid = true;

				++fields_iter.first;
			}
		}

		TypeMeta::TypeMeta() : m_type_name(k_unknown_type), m_is_valid(false) { m_fields.clear(); }

		TypeMeta TypeMeta::NewMetaFromName(std::string type_name)
		{
			TypeMeta f_type(type_name);
			return f_type;
		}

		bool TypeMeta::NewArrayAccessorFromName(std::string array_type_name, ArrayAccessor& accessor)
		{
			auto iter = m_array_map.find(array_type_name);

			if (iter != m_array_map.end())
			{
				ArrayAccessor new_accessor(iter->second);
				accessor = new_accessor;
				return true;
			}

			return false;
		}

		ReflectionInstance TypeMeta::NewFromNameAndPJson(std::string type_name, const PJson& json_context)
		{
			auto iter = m_class_map.find(type_name);

			if (iter != m_class_map.end())
			{
				return ReflectionInstance(TypeMeta(type_name), (std::get<1>(*iter->second)(json_context)));
			}

			return ReflectionInstance();
		}

		PJson TypeMeta::WriteByName(std::string type_name, void* instance)
		{
			auto iter = m_class_map.find(type_name);

			if (iter != m_class_map.end())
			{
				return std::get<2>(*iter->second)(instance);
			}

			return PJson();
		}

		std::string TypeMeta::GetTypeName() { return m_type_name; }

		int TypeMeta::GetFieldsList(FieldAccessor*& out_list)
		{
			int count = m_fields.size();
			out_list = new FieldAccessor[count];
			for (int i = 0; i < count; i++)
			{
				out_list[i] = m_fields[i];
			} 
			return count;
		}

		int TypeMeta::GetBaseClassReflectionInstanceList(ReflectionInstance*& out_list, void* instance)
		{
			auto iter = m_class_map.find(m_type_name);

			if (iter != m_class_map.end())
			{
				return (std::get<0>(*iter->second))(out_list, instance);
			}

			return 0;
		}

		FieldAccessor TypeMeta::GetFieldByName(const char* name)
		{
			const auto iter = std::find_if(m_fields.begin(), m_fields.end(), [&](const auto& i)
				{
					return std::strcmp(i.GetFieldName(), name) == 0;
				});

			if (iter != m_fields.end())
			{
				return *iter;
			}

			return FieldAccessor(nullptr);
		}

		TypeMeta& TypeMeta::operator=(const TypeMeta& dest)
		{
			if (this == &dest)
			{
				return *this;
			}
			m_fields.clear();
			m_fields = dest.m_fields;

			m_type_name = dest.m_type_name;
			m_is_valid = dest.m_is_valid;

			return *this;
		}

		FieldAccessor::FieldAccessor()
		{
			m_field_name = k_unknown_type;
			m_field_name = k_unknown;
			m_functions = nullptr;
		}

		FieldAccessor::FieldAccessor(FieldFunctionTuple* functions) : m_functions(functions)
		{
			m_field_type_name = k_unknown_type;
			m_field_name = k_unknown;
			if (m_functions == nullptr)
			{
				return;
			}

			m_field_type_name = (std::get<4>(*m_functions))();
			m_field_name = (std::get<3>(*m_functions))();
		}

		void* FieldAccessor::Get(void* instance)
		{
			return static_cast<void*>((std::get<1>(*m_functions))(instance));
		}

		void FieldAccessor::Set(void* instance, void* value)
		{
			(std::get<0>(*m_functions))(instance, value);
		}

		TypeMeta FieldAccessor::GetOwnerTypeMeta()
		{
			TypeMeta f_type((std::get<2>(*m_functions))());
			return f_type;
		}

		bool FieldAccessor::GetTypeMeta(TypeMeta& field_type)
		{
			TypeMeta f_type(m_field_type_name);
			field_type = f_type;
			return f_type.m_is_valid;
		}

		const char* FieldAccessor::GetFieldName() const { return m_field_name; }
		const char* FieldAccessor::GetFieldTypeName() { return m_field_type_name; }

		bool FieldAccessor::IsArrayType()
		{
			return (std::get<5>(*m_functions))();
		}

		FieldAccessor& FieldAccessor::operator=(const FieldAccessor& dest)
		{
			if (this == &dest)
			{
				return *this;
			}

			m_functions = dest.m_functions;
			m_field_name = dest.m_field_name;
			m_field_type_name = dest.m_field_type_name;
			return *this;
		}

		ArrayAccessor::ArrayAccessor() : m_func(nullptr), m_array_type_name("UnKnowType"), m_element_type_name("UnKnowType")
		{

		}

		ArrayAccessor::ArrayAccessor(ArrayFunctionTuple* array_func) : m_func(array_func)
		{
			m_array_type_name = k_unknown_type;
			m_element_type_name = k_unknown_type;
			if (m_func == nullptr)
			{
				return;
			}

			m_array_type_name = std::get<3>(*m_func)();
			m_element_type_name = std::get<4>(*m_func)();
		}

		const char* ArrayAccessor::GetArrayTypeName() { return m_array_type_name; }
		const char* ArrayAccessor::GetElementTypeName() { return m_element_type_name; }
		void ArrayAccessor::Set(int index, void* instance, void* element_value)
		{
			size_t count = GetSize(instance);

			std::get<0>(*m_func)(index, instance, element_value);
		}

		void* ArrayAccessor::Get(int index, void* instance)
		{
			size_t count = GetSize(instance);

			return std::get<1>(*m_func)(index, instance);
		}

		int ArrayAccessor::GetSize(void* instance)
		{
			return std::get<2>(*m_func)(instance);
		}

		ArrayAccessor& ArrayAccessor::operator=(ArrayAccessor& dest)
		{
			if (this == &dest)
			{
				return *this;
			}
			m_func = dest.m_func;
			m_array_type_name = dest.m_array_type_name;
			m_element_type_name = dest.m_element_type_name;
			return *this;
		}

		ReflectionInstance& ReflectionInstance::operator=(ReflectionInstance& dest)
		{
			if (this == &dest)
			{
				return *this;
			}

			m_instance = dest.m_instance;
			m_meta = dest.m_meta;

			return *this;
		}

		ReflectionInstance& ReflectionInstance::operator=(ReflectionInstance&& dest)
		{
			if (this == &dest)
			{
				return *this;
			}

			m_instance = dest.m_instance;
			m_meta = dest.m_meta;

			return *this;
		}
	}
}