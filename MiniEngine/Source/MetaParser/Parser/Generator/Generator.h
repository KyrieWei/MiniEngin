#pragma once
#include "Common/SchemaModule.h"

#include <functional>
#include <string>

namespace Generator
{
    class GeneratorInterface
    {
    public:
        GeneratorInterface(std::string out_path, std::string root_path, std::function<std::string(std::string)> get_include_func) : 
            m_out_path(out_path), m_root_path(root_path), m_get_include_func(get_include_func) {}

        virtual int Generate(std::string path, SchemaModule schema) = 0;

        virtual void Finish() {};

        virtual ~GeneratorInterface() {};

    protected:
        virtual void PrepareStatus(std::string path);
        virtual void GenClassRenderData(std::shared_ptr<Class> class_temp, Mustache::data& class_def);
        virtual void GenClassFieldRenderData(std::shared_ptr<Class> class_temp, Mustache::data& field_defs);
        virtual std::string ProcessFileName(std::string path) = 0;

        std::string m_out_path{"gen_src"};
        std::string m_root_path;
        std::function<std::string(std::string)> m_get_include_func;

    };
}