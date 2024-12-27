#include "PickerPipeline.h"

PickerPipeline::PickerPipeline()
{
    m_Stride = sizeof(VertexBase);
    m_Shader = Shader("resources/shaders/picker.wgsl");
    m_Attributes.push_back(VertexAttribCreator::PositionAttrib());
    m_Attributes.push_back(VertexAttribCreator::NormalAttrib());
    m_Attributes.push_back(VertexAttribCreator::UVAttrib());

    uint32_t index = 0;

    // unique among models. no need dynamic
    m_UniformBindGroupOptions.push_back({index++, BindGroupType::BUFFER, UniformBufferType::VP, sizeof(ViewProjectionUniform), false, "vp"});

    // per model
    m_UniformBindGroupOptions.push_back({index++, BindGroupType::BUFFER, UniformBufferType::MODEL, sizeof(ModelUniform), true, "model"});
    m_UniformBindGroupOptions.push_back({index++, BindGroupType::BUFFER, UniformBufferType::PICKER, sizeof(glm::vec4), true, "pickcolor"});
    
}

void PickerPipeline::CreateBindGroupLayout()
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
void PickerPipeline::CreatePipeline()
{
    BindGroupLayout layouts[1] = {m_UniformBindGroupLayout};
    m_RenderPipeline = WGPUContext::CreateRenderPipeline(m_Shader, m_Attributes, m_Stride, layouts, 1);
}