#include "SampleColoredPipeline.h"

SampleColoredPipeline::SampleColoredPipeline()
{
    m_Shader = Shader("resources/shaders/single_geo_color_sample.wgsl");

    uint32_t index = 0;

    // unique among models. no need dynamic
    m_UniformBindGroupOptions.push_back({index++, BindGroupType::BUFFER, UniformBufferType::VP, sizeof(ViewProjectionUniform), false, "vp"});
    m_UniformBindGroupOptions.push_back({index++, BindGroupType::BUFFER, UniformBufferType::TIME, sizeof(float), false, "time"});
    m_UniformBindGroupOptions.push_back({index++, BindGroupType::BUFFER, UniformBufferType::LIGHT, sizeof(LightUniform), false, "light"});
    m_UniformBindGroupOptions.push_back({index++, BindGroupType::BUFFER, UniformBufferType::COUNT, sizeof(CountUniform), false, "count"});

    // per model
    m_UniformBindGroupOptions.push_back({index++, BindGroupType::BUFFER, UniformBufferType::MODEL, sizeof(ModelUniform), true, "model"});
    m_UniformBindGroupOptions.push_back({index++, BindGroupType::BUFFER, UniformBufferType::VEC4, sizeof(glm::vec4), true, "color"});


    for (auto & bindGroupOption : m_UniformBindGroupOptions)
    {
        if (bindGroupOption.bindGroupType == BindGroupType::BUFFER)
        {
            m_UniformBuffers.push_back(UniformBuffer::GetByType(bindGroupOption.uniformBufferType));
        }
    }
}

void SampleColoredPipeline::CreateBindGroupLayout()
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
}

void SampleColoredPipeline::CreatePipeline()
{
    BindGroupLayout layouts[1] = {m_UniformBindGroupLayout};
    m_RenderPipeline = WGPUContext::CreateRenderPipeline(m_Shader, m_Attributes, m_Stride, layouts, 1);

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