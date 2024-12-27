#include "RayRenderPhase.h"

#include "../../geometry/Geometry.h"

RayRenderPhase::RayRenderPhase()
{
    m_Pipeline = RaytracingSimplePipeline::Get();
   
}
void RayRenderPhase::RenderByRenderPass(RenderPassEncoder &renderPass, void ** context) 
{
    if (!m_hasBindGroupCreated) {
         CreateBindGroups();
         m_hasBindGroupCreated = true;
    }

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


void RayRenderPhase::CreateTextureBindGroup()
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
    //AppendTextureBindGroupEntry(bindGroupEntries, index, TextureType::ALBEDO);

   // BindGroupEntry binding{};
   // binding.binding = 0;
   // binding.textureView = m_NoiseTexture.GetOrCreateTextureView();

   // bindGroupEntries.push_back(binding);

    //AppendTextureBindGroupEntry(bindGroupEntries, index, TextureType::ALBEDO);
    //AppendTextureBindGroupEntry(bindGroupEntries, index, TextureType::NORMAL);
    //AppendTextureBindGroupEntry(bindGroupEntries, index, TextureType::ROUGHNESS);
    

    
    for (int i = 0; i < m_Textures.size(); i++)
    {
         BindGroupEntry binding{};
        binding.binding = i;
        binding.textureView = m_Textures[i].get()->GetOrCreateTextureView();//m_InputTextureObjects[type].get()->GetOrCreateTextureView();
        bindGroupEntries.push_back(binding);
    }

    FillRemainingBindGroupEntry(bindGroupEntries, m_Textures.size());

    bindGroupDesc.entryCount = bindGroupEntries.size();
    bindGroupDesc.entries = bindGroupEntries.data();

    m_TextureBindGroup = WGPUContext::device.createBindGroup(bindGroupDesc);
    m_TextureBindGroup.setLabel("debug window texture bind group");
}