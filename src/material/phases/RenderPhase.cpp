#include "RenderPhase.h"

RenderPhase::~RenderPhase()
{
    WGPUContext::ReleaseIfNotNull(m_UniformBindGroup);
    WGPUContext::ReleaseIfNotNull(m_UniformBindGroup);
    WGPUContext::ReleaseIfNotNull(m_TextureBindGroup);
    WGPUContext::ReleaseIfNotNull(m_SamplerBindGroup);
}

std::vector<uint32_t> RenderPhase::GetDynamicOffsets(uint16_t index)
{
    std::vector<uint16_t> strides = m_Pipeline->GetDynamicOffsetStrides();
    std::vector<uint32_t> offsets;
    offsets.resize(strides.size());
    std::transform(std::begin(strides), std::end(strides), std::begin(offsets), [index](int stride){
        return index * stride;
    });
    return offsets;
}

uint8_t RenderPhase::GetDynamicOffsetCount()
{
    return m_Pipeline->GetDynamicOffsetCount();
}

void RenderPhase::CreateUniformBindGroup()
{
    WGPUContext::ReleaseIfNotNull(m_UniformBindGroup);
    //uniform
    std::vector<BindGroupEntry> bindGroupEntries;

    BindGroupLayout uniformBindGroupLayout = m_Pipeline->GetUniformBindGroupLayout();
    uniformBindGroupLayout.setLabel("uniform");

    auto bindGroupOptions = m_Pipeline->GetUniformBindGroupOptions();
    BindGroupDescriptor bindGroupDesc{};
    bindGroupDesc.layout = uniformBindGroupLayout;
    bindGroupDesc.entryCount = bindGroupOptions.size();
    bindGroupDesc.label = "uniform";

    for (auto & bindGroupOption: bindGroupOptions)
    {
        bindGroupEntries.push_back(bindGroupOption.CreateUniformBindGroupEntry());
    }

    bindGroupDesc.entryCount = bindGroupEntries.size();
    bindGroupDesc.entries = bindGroupEntries.data();

    m_UniformBindGroup = WGPUContext::device.createBindGroup(bindGroupDesc);
    m_UniformBindGroup.setLabel("uniform");
}