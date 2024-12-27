#include "PickerRenderPhase.h"
#include "../../geometry/Geometry.h"

PickerRenderPhase::PickerRenderPhase()
{
   m_Pipeline = PickerPipeline::Get();
   CreateBindGroups();
}
void PickerRenderPhase::RenderByRenderPass(RenderPassEncoder &renderPass, void ** context)
{
    renderPass.setPipeline(m_Pipeline->GetRenderPipeline());
    Geometry * geo = static_cast<Geometry*>(context[0]);
    int uniformIndex = geo->GetUniformIndex();
    renderPass.setBindGroup(0, m_UniformBindGroup, this->GetDynamicOffsetCount(), this->GetDynamicOffsets(uniformIndex).data());

    Buffer buffer = geo->GetBuffer();
    Buffer index = geo->GetIndexBuffer();
    UpdatePickerColor(geo);
    renderPass.setVertexBuffer(0, buffer, 0, buffer.getSize());
    renderPass.setIndexBuffer(index, IndexFormat::Uint32, 0, index.getSize());
    renderPass.drawIndexed(geo->GetIndexCount(), 1, 0, 0, 0);
}

void PickerRenderPhase::UpdatePickerColor(Geometry * geo)
{
    glm::vec4 pickId = geo->GetPickId();
    UniformBuffer *buffer = PickerUniformBuffer::Get();
    WGPUContext::queue.writeBuffer(buffer->GetBuffer(), geo->GetUniformIndex() * buffer->GetStride(),&pickId, buffer->GetUnitSize());
}

void PickerRenderPhase::CreateBindGroups()
{
    CreateUniformBindGroup();
}