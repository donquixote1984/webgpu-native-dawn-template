#pragma once
#include <iostream>
#include <fstream>
#include <filesystem>
#include <sstream>
#include <boost/algorithm/string.hpp>
#include <webgpu/webgpu.hpp>

using namespace wgpu;
class Shader
{
public:
    Shader(){}
    Shader(const std::string &path);
    std::string & GetSource();
    ShaderModule GetShaderModule();
private:
    std::string ResolveIncludeLine(const std::string &line, const std::string & currentPath);
    std::string ResolveInclude(const std::string& filepath);
    std::string m_Source;
};