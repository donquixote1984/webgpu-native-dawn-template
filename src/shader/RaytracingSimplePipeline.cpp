#include "RaytracingSimplePipeline.h"

RaytracingSimplePipeline::RaytracingSimplePipeline()
{
    m_Shader = Shader("resources/shaders/ray_tracing_simple.wgsl");

    m_Stride = sizeof(VertexBase);
    m_Attributes.push_back(VertexAttribCreator::PositionAttrib());
    m_Attributes.push_back(VertexAttribCreator::NormalAttrib());
    m_Attributes.push_back(VertexAttribCreator::UVAttrib());


    uint32_t index = 0;
    // add a sample uniform bindgroup
    m_UniformBindGroupOptions.push_back({index++, BindGroupType::BUFFER, UniformBufferType::TIME, sizeof(float), false, "time"});
    m_UniformBindGroupOptions.push_back({index++, BindGroupType::BUFFER, UniformBufferType::CAM_POS, sizeof(glm::vec4), false, "camPos"});
    m_UniformBindGroupOptions.push_back({index++, BindGroupType::BUFFER, UniformBufferType::SCREEN, sizeof(ScreenUniform), false, "screen"});
    m_UniformBindGroupOptions.push_back({index++, BindGroupType::BUFFER, UniformBufferType::VP, sizeof(ViewProjectionUniform), false, "vp"});
    m_UniformBindGroupOptions.push_back({index++, BindGroupType::BUFFER, UniformBufferType::BVH, sizeof(BVHUniform), false, "bvh"});
    m_UniformBindGroupOptions.push_back({index++, BindGroupType::BUFFER, UniformBufferType::HITABLE, sizeof(HitableListUniform), false, "hitable"});


    
    for (uint32_t i = 0; i < constants::MAX_TEXTURE_SLOT; i++)
    {
        m_TextureBindGroupOptions.push_back({i, BindGroupType::TEXTURE});
    }
    
    // samplers
    m_SamplerBindGroupOptions.push_back({0, BindGroupType::SAMPLER});

}
void RaytracingSimplePipeline::CreatePipeline()
{
    BindGroupLayout layouts[3] = {m_UniformBindGroupLayout, m_TextureBindGroupLayout, m_SamplerBindGroupLayout };
    m_RenderPipeline = WGPUContext::CreateRenderPipeline(m_Shader, m_Attributes, m_Stride, layouts, 3);

    BindGroupLayout uniformBindGroupLayout = m_UniformBindGroupLayout;
    uniformBindGroupLayout.setLabel("uniform");

    auto bindGroupOptions = m_UniformBindGroupOptions;
    BindGroupDescriptor bindGroupDesc{};
    bindGroupDesc.layout = uniformBindGroupLayout;
    bindGroupDesc.entryCount = bindGroupOptions.size();
    bindGroupDesc.label = "uniform";

    std::vector<BindGroupEntry> bindGroupEntries;
    for (auto & bindGroupOption: bindGroupOptions)
    {
        bindGroupEntries.push_back(bindGroupOption.CreateUniformBindGroupEntry());
    }
    bindGroupDesc.entryCount = bindGroupEntries.size();

    bindGroupDesc.entries = bindGroupEntries.data();

    m_UniformBindGroup = WGPUContext::device.createBindGroup(bindGroupDesc);
    m_UniformBindGroup.setLabel("uniform");
}

void RaytracingSimplePipeline::CreateBindGroupLayout()
{
      // uniform
    BindGroupLayoutDescriptor uniformBindGroupLayoutDesc{};
    uniformBindGroupLayoutDesc.entryCount = m_UniformBindGroupOptions.size();
    std::vector<BindGroupLayoutEntry> entries(m_UniformBindGroupOptions.size());

    std::transform(m_UniformBindGroupOptions.begin(), m_UniformBindGroupOptions.end(), entries.begin(), [](BindGroupOptions & option){
        return option.CreateBindGroupLayoutEntry();
    });

    uniformBindGroupLayoutDesc.entries = entries.data();
    m_UniformBindGroupLayout = WGPUContext::device.createBindGroupLayout(uniformBindGroupLayoutDesc);

    // texture 
    BindGroupLayoutDescriptor textureBindGroupLayoutDesc{}; 
    textureBindGroupLayoutDesc.entryCount = m_TextureBindGroupOptions.size();
    std::vector<BindGroupLayoutEntry> entries2(m_TextureBindGroupOptions.size());
        std::transform(m_TextureBindGroupOptions.begin(), m_TextureBindGroupOptions.end(), entries2.begin(), [](BindGroupOptions & option){
        return option.CreateBindGroupLayoutEntry();
    });
    textureBindGroupLayoutDesc.entries = entries2.data();
    m_TextureBindGroupLayout = WGPUContext::device.createBindGroupLayout(textureBindGroupLayoutDesc);

    // samplers
    BindGroupLayoutDescriptor samplerBindGroupLayoutDesc{}; 
    samplerBindGroupLayoutDesc.entryCount = m_SamplerBindGroupOptions.size();
    std::vector<BindGroupLayoutEntry> entries3(m_SamplerBindGroupOptions.size());
        std::transform(m_SamplerBindGroupOptions.begin(), m_SamplerBindGroupOptions.end(), entries3.begin(), [](BindGroupOptions & option){
        return option.CreateBindGroupLayoutEntry();
    });
    samplerBindGroupLayoutDesc.entries = entries3.data();
    m_SamplerBindGroupLayout = WGPUContext::device.createBindGroupLayout(samplerBindGroupLayoutDesc);
}

