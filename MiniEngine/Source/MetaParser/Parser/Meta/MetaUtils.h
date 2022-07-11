#pragma once

#include <vector>
#include <string>

#include "Cursor/Cursor.h"
#include "Common/Precompiled.h"

namespace Utils
{
    void ToString(const CXString& str, std::string& output);

    fs::path MakeRelativePath(const fs::path& from, const fs::path& to);

    std::string FormatQualifiedName(std::string& source_string);

    std::string GetFileName(std::string path);

    std::string GetNameWithoutFirstM(std::string& name);

    std::string GetTypeNameWithoutNamespace(const CursorType& type);

    std::string GetNameWithoutContainer(std::string name);

    std::string GetStringWithoutQuot(std::string& input);

    std::vector<std::string> Split(std::string input, std::string pat);

    std::string Replace(std::string& source_string, std::string sub_string, const std::string new_string);

    std::string Replace(std::string& source_string, char target_char, const char new_char);

    std::string ToUpper(std::string& source_string);

    std::string Trim(std::string& source_string, const std::string trim_chars);

    std::string LoadFile(std::string path);

    void SaveFile(const std::string& output_string, const std::string& output_file);

    void ReplaceAll(std::string& resource_str, std::string sub_str, std::string new_str);

    unsigned long FormatPathString(const std::string& path_string, std::string& out_string);

} // namespace Utils
