#include "../../geometry/Geometry.h"
#include "DebugWindowRenderPhase.h"

DebugWindowRenderPhase::DebugWindowRenderPhase()
{
    m_Pipeline = DebugWindowPipeline::Get();
}

void DebugWindowRenderPhase::CreateBindGroups()
{
    CreateUniformBindGroup();
    CreateTextureBindGroup();
    CreateSamplerBindGroup();
}


void DebugWindowRenderPhase::CreateTextureBindGroup()
{
    if (m_TextureBindGroup != nullptr)
    {
        m_TextureBindGroup.release();
        m_TextureBindGroup = nullptr;
    }
    // the textureview changes every frame. 
    // should recreate bindgroup every frame.

    // texture bind group
    std::vector<BindGroupEntry> bindGroupEntries;
    BindGroupLayout textureBindGroupLayout = m_Pipeline->GetTextureBindGroupLayout();
    textureBindGroupLayout.setLabel("debug window texture bind group layout");
    auto bindGroupOptions = m_Pipeline->GetTextureBindGroupOptions();
    BindGroupDescriptor bindGroupDesc{};
    bindGroupDesc.layout = textureBindGroupLayout;
    bindGroupDesc.entryCount = bindGroupOptions.size();
    bindGroupDesc.label = "debug window texture bind group descriptor";
    int index = 0;
    //AppendTextureBindGroupEntry(bindGroupEntries, index, TextureType::ALBEDO);

    BindGroupEntry binding{};
    binding.binding = 0;
    binding.textureView = m_TextureView;
    bindGroupEntries.push_back(binding);

    bindGroupDesc.entryCount = bindGroupEntries.size();
    bindGroupDesc.entries = bindGroupEntries.data();

    m_TextureBindGroup = WGPUContext::device.createBindGroup(bindGroupDesc);
    m_TextureBindGroup.setLabel("debug window texture bind group");
}

void DebugWindowRenderPhase::CreateSamplerBindGroup()
{
    if (m_SamplerBindGroup != nullptr)
    {
        m_SamplerBindGroup.release();
        m_SamplerBindGroup = nullptr;
    }
    // sampler
    std::vector<BindGroupEntry> bindGroupEntries;
    BindGroupLayout samplerBindGroupLayout = m_Pipeline->GetSamplerBindGroupLayout();
    samplerBindGroupLayout.setLabel("debug window sampler");
    auto bindGroupOptions = m_Pipeline->GetSamplerBindGroupOptions();
    BindGroupDescriptor bindGroupDesc{};
    bindGroupDesc.layout = samplerBindGroupLayout;
    bindGroupDesc.entryCount = bindGroupOptions.size();
    bindGroupDesc.label = "debug window sampler";

    int index = 0;
    for (auto & bindGroupOption: bindGroupOptions)
    {
        BindGroupEntry binding{};
        binding.binding = index;
        binding.sampler = SamplerObject::Get()->GetSampler();
        bindGroupEntries.push_back(binding);
        index ++;
    }

    bindGroupDesc.entryCount = bindGroupEntries.size();
    bindGroupDesc.entries = bindGroupEntries.data();

    m_SamplerBindGroup = WGPUContext::device.createBindGroup(bindGroupDesc);
    m_SamplerBindGroup.setLabel("debug window sampler bind group");
}


void DebugWindowRenderPhase::RenderByRenderPass(RenderPassEncoder &renderPass, void ** context) 
{
    //CreateBindGroups();
    renderPass.setPipeline(m_Pipeline->GetRenderPipeline());
    Geometry * geo = static_cast<Geometry*>(context[0]);
    int uniformIndex = geo->GetUniformIndex();
    renderPass.setBindGroup(0, m_UniformBindGroup, this->GetDynamicOffsetCount(), this->GetDynamicOffsets(uniformIndex).data());
    if (m_TextureBindGroup) 
    {
        renderPass.setBindGroup(1, m_TextureBindGroup, 0, nullptr);
    }
    if (m_SamplerBindGroup)
    {
        renderPass.setBindGroup(2, m_SamplerBindGroup, 0, nullptr);
    }

    Buffer buffer = geo->GetBuffer();
    Buffer index = geo->GetIndexBuffer();
    renderPass.setVertexBuffer(0, buffer, 0, buffer.getSize());
    renderPass.setIndexBuffer(index, IndexFormat::Uint32, 0, index.getSize());
    renderPass.drawIndexed(geo->GetIndexCount(), 1, 0, 0, 0);
    //m_TextureView.release();
    //m_TextureView = nullptr;
}