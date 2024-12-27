#include "Shader.h"
#include "../Application.h"

Shader::Shader(const std::string &shaderPath)
{
    if (!std::filesystem::exists(shaderPath)) {
        std::cerr << "invalid shader path!" << std::endl;
        assert(0);
    }
    m_Source = ResolveInclude(shaderPath);
}

std::string & Shader::GetSource()
{
    return m_Source;
}

std::string Shader::ResolveInclude(const std::string& filepath)
{
	std::string line;
	std::stringstream includestream;

    std::fstream stream(filepath);
    while (getline(stream, line))
    {
        std::string resolvedLine = ResolveIncludeLine(line, filepath);
        includestream << resolvedLine << "\n";
    }
    stream.close();
	return includestream.str();
}

std::string Shader::ResolveIncludeLine(const std::string &line, const std::string & currentPath)
{
	std::string replaceline = line;
	if (replaceline.find("#include") != std::string::npos)
	{
		boost::replace_all(replaceline, "#include", "");
		boost::trim(replaceline);
		replaceline = replaceline.substr(1, replaceline.length()-2);
		std::filesystem::path path = currentPath;
		auto includepath = path.parent_path().append(replaceline);
		if (std::filesystem::exists(includepath)) 
		{
			std::string includecontent = ResolveInclude(includepath);
			return includecontent;
		} else {
			return "";
		} 
	} else {
		return replaceline;
	}
}

ShaderModule Shader::GetShaderModule()
{
	wgpu::ShaderModuleDescriptor shaderDesc;
    
    wgpu::ShaderModuleWGSLDescriptor shaderCodeDesc;
// Set the chained struct's header
    shaderCodeDesc.chain.next = nullptr;
    shaderCodeDesc.chain.sType = wgpu::SType::ShaderModuleWGSLDescriptor;
// Connect the chain
    shaderDesc.nextInChain = &shaderCodeDesc.chain;
    shaderCodeDesc.code = GetSource().c_str();
    wgpu::ShaderModule shaderModule = WGPUContext::device.createShaderModule(shaderDesc);
    return shaderModule;
}