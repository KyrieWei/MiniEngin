#pragma once
#include "Common/Precompiled.h"

class TemplateManager
{
public:
    static TemplateManager* GetInstance()
    {
        static TemplateManager* m_pInstance;
        if(m_pInstance == nullptr)
        {
            m_pInstance = new TemplateManager();
        }

        return m_pInstance;
    }

    void LoadTemplates(std::string path, std::string template_name);

    std::string RenderByTemplate(std::string template_name, Mustache::data& template_data);

private:
    TemplateManager() {}
    TemplateManager(const TemplateManager&);
    TemplateManager& operator=(const TemplateManager&);
    std::unordered_map<std::string, std::string> m_template_pool;

};