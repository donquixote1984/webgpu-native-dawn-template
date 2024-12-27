#include "ShadowMapCSMPhase.h"
#include "../../geometry/Geometry.h"

ShadowMapCSMPhase::ShadowMapCSMPhase()
{
    m_Pipeline = ShadowMapCSMPipeline::Get();
    CreateBindGroups();
}

std::vector<uint32_t> ShadowMapCSMPhase::GetDynamicOffsetsAndCSM(uint16_t index, int csmIndex)
{
    std::vector<uint32_t> offsets;
    
    for (auto option: m_Pipeline->GetUniformBindGroupOptions())
    {
        if (option.dynamic) 
        {
            int stride = UniformBufferCreator::CalculateStride(option.size);
            if (option.label == "csm_index")
            {
                offsets.push_back(csmIndex * stride);
            } else {
                offsets.push_back(index * stride);
            }
        }
    }
    return offsets;
}


void ShadowMapCSMPhase::RenderByRenderPass(RenderPassEncoder &renderPass, void ** context)
{
    renderPass.setPipeline(m_Pipeline->GetRenderPipeline());
    Geometry * geo = static_cast<Geometry*>(context[0]);
    int *csmIndex = static_cast<int *>(context[1]);

    int uniformIndex = geo->GetUniformIndex();

    renderPass.setBindGroup(0, m_UniformBindGroup, this->GetDynamicOffsetCount(), GetDynamicOffsetsAndCSM(uniformIndex, *csmIndex).data());

    Buffer buffer = geo->GetBuffer();
    Buffer index = geo->GetIndexBuffer();
    renderPass.setVertexBuffer(0, buffer, 0, buffer.getSize());
    renderPass.setIndexBuffer(index, IndexFormat::Uint32, 0, index.getSize());
    renderPass.drawIndexed(geo->GetIndexCount(), 1, 0, 0, 0);
}