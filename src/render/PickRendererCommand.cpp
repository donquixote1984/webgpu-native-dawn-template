#include "PickRendererCommand.h"


//void PickRendererCommand::UpdatePickerColor()
//{
    /*
    glm::vec4 pickId = m_GeoPtr->GetPickId();
    UniformBuffer *buffer = PickerUniformBuffer::Get();
    WGPUContext::queue.writeBuffer(buffer->GetBuffer(), m_GeoPtr->GetUniformIndex() * buffer->GetStride(),&pickId, buffer->GetUnitSize());
    */
//}
void PickRendererCommand::PostCommandSubmit()
{
    //handle = m_PickRenderPass.GetBuffer().mapAsyncF(MapMode::Read, 0, sizeof(glm::vec4), info);
    //m_PickRenderPass.GetBuffer().mapAsyncF(MapMode::Read, 0, sizeof(glm::vec4), info);
    handle = m_PickRenderPass.GetBuffer().mapAsync(MapMode::Read, 0, sizeof(glm::vec4), [&](WGPUBufferMapAsyncStatus status){
        if (status == BufferMapAsyncStatus::Success)
        {
            unsigned char * output = (unsigned char*)m_PickRenderPass.GetBuffer().getConstMappedRange(0, sizeof(glm::vec4));
            //std::cout << output[0] << " "<< output[1] <<" "<<output[2]<< std::endl;
            int r = output[0];
            int g = output[1];
            int b = output[2];
            int a = output[3];
            int index = (r | (g << 8) | (b << 16) | (b << 24)) - 1;
            if (index > 0)
            {
            SceneUI::Get()->SelectGeometry(index);
            }
        }
        m_PickRenderPass.GetBuffer().unmap();
    });
}