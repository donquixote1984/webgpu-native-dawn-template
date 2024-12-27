#include "ShadowMapCSMPipeline.h"

ShadowMapCSMPipeline::ShadowMapCSMPipeline()
{
    m_Shader = Shader("resources/shaders/shadow_map_csm.wgsl");

    uint32_t index = 0;
    // unique among models. no need dynamic
    //m_UniformBindGroupOptions.push_back({index++, BindGroupType::BUFFER, UniformBufferType::CSM, sizeof(CSMUniform), false, "csm"});
    m_UniformBindGroupOptions.push_back({index++, BindGroupType::BUFFER, UniformBufferType::LIGHT, sizeof(LightUniform), false, "light"});
    // per model
    m_UniformBindGroupOptions.push_back({index++, BindGroupType::BUFFER, UniformBufferType::CSMINDEX, sizeof(int), true, "csm_index"});
    m_UniformBindGroupOptions.push_back({index++, BindGroupType::BUFFER, UniformBufferType::MODEL, sizeof(ModelUniform), true, "model"});
}

void ShadowMapCSMPipeline::CreateBindGroupLayout()
{
    BindGroupLayoutDescriptor uniformBindGroupLayoutDesc{};
    uniformBindGroupLayoutDesc.entryCount = m_UniformBindGroupOptions.size();
    std::vector<BindGroupLayoutEntry> entries(m_UniformBindGroupOptions.size());

    std::transform(m_UniformBindGroupOptions.begin(), m_UniformBindGroupOptions.end(), entries.begin(), [](BindGroupOptions & option){
        return option.CreateBindGroupLayoutEntry();
    });

    uniformBindGroupLayoutDesc.entries = entries.data();
    m_UniformBindGroupLayout = WGPUContext::device.createBindGroupLayout(uniformBindGroupLayoutDesc);
}
void ShadowMapCSMPipeline::CreatePipeline()
{
    BindGroupLayout layouts[1] = {m_UniformBindGroupLayout};
    m_RenderPipeline = WGPUContext::CreateDepthOnlyRenderPipeline(m_Shader, m_Attributes, m_Stride, layouts, 1);
}