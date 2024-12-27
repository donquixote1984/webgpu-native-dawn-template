#include "DebugDepthRenderPhase.h"
DebugDepthRenderPhase::DebugDepthRenderPhase()
{
     m_Pipeline = DebugDepthPipeline::Get();
}
void DebugDepthRenderPhase::CreateTextureBindGroup()
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