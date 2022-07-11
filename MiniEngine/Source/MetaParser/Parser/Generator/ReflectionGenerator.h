#pragma once
#include "Generator.h"

namespace Generator
{
    class ReflectionGenerator : public GeneratorInterface
    {
    public:
        ReflectionGenerator() = delete;
        ReflectionGenerator(std::string source_directory, std::function<std::string(std::string)> get_include_function);
        virtual int Generate(std::string path, SchemaModule shcema) override;
        virtual void Finish() override;
        virtual ~ReflectionGenerator() override;

    protected:
        virtual void PrepareStatus(std::string path) override;
        virtual std::string ProcessFileName(std::string path) override;

    private:
        std::vector<std::string> m_head_file_list;
        std::vector<std::string> m_type_list;
    };
}