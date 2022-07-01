#include "Parser.h"

void MetaParser::Prepare(void) {}

std::string MetaParser::GetIncludeFile(std::string name)
{
    auto iter = m_type_table.find(name);
    return iter == m_type_table.end() ? std::string() : iter->second;
}

MetaParser::MetaParser( const std::string project_input_file,
                        const std::string include_file_path,
                        const std::string include_path,
                        const std::string include_sys,
                        const std::string module_name,
                        bool              is_show_errors) :
                        m_project_input_file(project_input_file),
                        m_source_include_file_name(include_file_path),
                        m_sys_include(include_sys), m_module_name(module_name), m_is_show_errors(is_show_errors)
{
    m_work_paths = Utils::split(include_path, ";");
}



MetaParser::~MetaParser(void)
{

}

void MetaParser::Finish(void)
{

}

bool MetaParser::ParseProject()
{
    return true;
}

int MetaParser::Parse(void)
{
    return 0;
}

void MetaParser::GenerateFiles(void)
{

}

void MetaParser::BuildClassAST()
{

}