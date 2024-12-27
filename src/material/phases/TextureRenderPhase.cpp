#include "TextureRenderPhase.h"
#include "../../geometry/Geometry.h"

TextureRenderPhase::TextureRenderPhase()
{
    m_Pipeline = TexturedGeometryPipeline::Get();
}

void TextureRenderPhase::CreateTextureBindGroup()
{
    WGPUContext::ReleaseIfNotNull(m_TextureBindGroup);
    // texture bind group
    std::vector<BindGroupEntry> bindGroupEntries;
    BindGroupLayout textureBindGroupLayout = m_Pipeline->GetTextureBindGroupLayout();
    textureBindGroupLayout.setLabel("texture");
    auto bindGroupOptions = m_Pipeline->GetTextureBindGroupOptions();
    BindGroupDescriptor bindGroupDesc{};
    bindGroupDesc.layout = textureBindGroupLayout;
    bindGroupDesc.entryCount = bindGroupOptions.size();
    bindGroupDesc.label = "texture";
    int index = 0;
    AppendTextureBindGroupEntry(bindGroupEntries, index, TextureType::ALBEDO);
    AppendTextureBindGroupEntry(bindGroupEntries, index, TextureType::NORMAL);
    AppendTextureBindGroupEntry(bindGroupEntries, index, TextureType::ROUGHNESS);
    // adding other textures

    FillRemainingBindGroupEntry(bindGroupEntries, index);

    //AppendTextureBindGroupEntry(bindGroupEntries, (int)constants::BINDING_SHADOW_MAP, TextureType::SHADOW_MAP);
    if (m_ReceiveShadow)
    {
        AppendTextureBindGroupEntryFixed(bindGroupEntries, constants::BINDING_SHADOW_MAP, TextureType::SHADOW_MAP);
    }

    bindGroupDesc.entryCount = bindGroupEntries.size();
    bindGroupDesc.entries = bindGroupEntries.data();

    m_TextureBindGroup = WGPUContext::device.createBindGroup(bindGroupDesc);
    m_TextureBindGroup.setLabel("texture");
}



void TextureRenderPhase::CreateSamplerBindGroup()
{
    WGPUContext::ReleaseIfNotNull(m_SamplerBindGroup);
    // sampler
    std::vector<BindGroupEntry> bindGroupEntries;
    BindGroupLayout samplerBindGroupLayout = m_Pipeline->GetSamplerBindGroupLayout();
    samplerBindGroupLayout.setLabel("sampler");
    auto bindGroupOptions = m_Pipeline->GetSamplerBindGroupOptions();
    BindGroupDescriptor bindGroupDesc{};
    bindGroupDesc.layout = samplerBindGroupLayout;
    bindGroupDesc.entryCount = bindGroupOptions.size();
    bindGroupDesc.label = "sampler";

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
    m_SamplerBindGroup.setLabel("sampler");
}

void TextureRenderPhase::CreateBindGroups()
{
    CreateUniformBindGroup();
    CreateTextureBindGroup();
    CreateSamplerBindGroup();
}


void TextureRenderPhase::RenderByRenderPass(RenderPassEncoder &renderPass, void ** context) 
{
    if (!m_hasBindGroupCreated) {
        CreateBindGroups();
        m_hasBindGroupCreated = true;
    }
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
}