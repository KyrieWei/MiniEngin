#include "Common/Precompiled.h"

#include "ReflectionGenerator.h"

#include "LanguageTypes/Class.h"
#include "TemplateManager/TemplateManager.h"

#include <map>
#include <set>

namespace Generator
{
    ReflectionGenerator::ReflectionGenerator(std::string source_directory, std::function<std::string(std::string)> get_include_function) : 
        GeneratorInterface(source_directory + "/_generated/reflection", source_directory, get_include_function)
    {
        PrepareStatus(m_out_path);
    }

    void ReflectionGenerator::PrepareStatus(std::string path)
    {
        GeneratorInterface::PrepareStatus(path);
        TemplateManager::GetInstance()->LoadTemplates(m_root_path, "CommonReflectionFile");
        TemplateManager::GetInstance()->LoadTemplates(m_root_path, "AllReflectionFile");
        return;
    }

    std::string ReflectionGenerator::ProcessFileName(std::string path)
    {
        auto relativeDir = fs::path(path).filename().replace_extension("reflection.gen.h").string();
        return m_out_path + "/" + relativeDir;
    }

    int ReflectionGenerator::Generate(std::string path, SchemaModule schema)
    {
        static const std::string vector_prefix = "std::vector<";

        std::string file_path = ProcessFileName(path);
        Mustache::data mustache_data;
        Mustache::data include_headfiles(Mustache::data::type::list);
        Mustache::data class_defines(Mustache::data::type::list);

        include_headfiles.push_back(Mustache::data("headfile_name", Utils::MakeRelativePath(m_root_path, path).string()));

        std::map<std::string, bool> class_names;
        //class defs
        for(auto class_temp : schema.classes)
        {
            if(!class_temp->ShouldCompileFields())
                continue;
            
            class_names.insert_or_assign(class_temp->GetClassName(), false);
            class_names[class_temp->GetClassName()] = true;

            std::vector<std::string>                                   field_names;
            std::map<std::string, std::pair<std::string, std::string>> vector_map;

            Mustache::data class_def;
            Mustache::data vector_defines(Mustache::data::type::list);

            GenClassRenderData(class_temp, class_def);
            for (auto field : class_temp->m_fields)
            {
                if (!field->ShouldCompile())
                    continue;
                field_names.emplace_back(field->m_name);
                bool is_array = field->m_type.find(vector_prefix) == 0;
                if (is_array)
                {
                    std::string array_useful_name = field->m_type;

                    Utils::FormatQualifiedName(array_useful_name);

                    std::string item_type = field->m_type;

                    item_type = Utils::GetNameWithoutContainer(item_type);

                    vector_map[field->m_type] = std::make_pair(array_useful_name, item_type);
                }
            }
            if (vector_map.size() > 0)
            {
                if (nullptr == class_def.get("vector_exist"))
                {
                    class_def.set("vector_exist", true);
                }
                for (auto vector_item : vector_map)
                {
                    std::string    array_useful_name = vector_item.second.first;
                    std::string    item_type         = vector_item.second.second;
                    Mustache::data vector_define;
                    vector_define.set("vector_useful_name", array_useful_name);
                    vector_define.set("vector_type_name", vector_item.first);
                    vector_define.set("vector_element_type_name", item_type);
                    vector_defines.push_back(vector_define);
                }
            }
            class_def.set("vector_defines", vector_defines);
            class_defines.push_back(class_def);
        }

        mustache_data.set("class_defines", class_defines);
        mustache_data.set("include_headfiles", include_headfiles);
        std::string render_string =
            TemplateManager::GetInstance()->RenderByTemplate("CommonReflectionFile", mustache_data);
        Utils::SaveFile(render_string, file_path);

        for (auto class_item : class_names)
        {
            m_type_list.emplace_back(class_item.first);
        }

        m_head_file_list.emplace_back(Utils::MakeRelativePath(m_root_path, file_path).string());
        return 0;
    }

    void ReflectionGenerator::Finish()
    {
        Mustache::data mustache_data;
        Mustache::data include_headfiles = Mustache::data::type::list;
        Mustache::data class_defines     = Mustache::data::type::list;

        for (auto& head_file : m_head_file_list)
        {
            include_headfiles.push_back(Mustache::data("headfile_name", head_file));
        }
        for (auto& class_name : m_type_list)
        {
            class_defines.push_back(Mustache::data("class_name", class_name));
        }
        mustache_data.set("include_headfiles", include_headfiles);
        mustache_data.set("class_defines", class_defines);
        std::string render_string =
            TemplateManager::GetInstance()->RenderByTemplate("AllReflectionFile", mustache_data);
        Utils::SaveFile(render_string, m_out_path + "/all_reflection.h");        
    }

    ReflectionGenerator::~ReflectionGenerator() {}
}