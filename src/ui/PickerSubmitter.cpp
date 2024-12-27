#include "PickerSubmitter.h"
#include "../SceneUI.h"

void PickerSubmitter::SubmitRenderPass()
{
    /**
     * 
     *  WGPUCommandBufferDescriptor cmdBufferDescriptor = {};
        cmdBufferDescriptor.nextInChain = nullptr;
        cmdBufferDescriptor.label = "CMD";
        m_RenderPass.end();
        m_RenderPass.release();
        CommandBuffer cmdBuffer = m_CommandEncoder.finish(cmdBufferDescriptor);
        m_CommandEncoder.release();
        WGPUContext::queue.submit(1, &cmdBuffer);
        //
        cmdBuffer.release();

     * **/
    ImageCopyTexture texture;
    texture.texture = m_PickerTexture;
    texture.origin = {(uint32_t)m_Interactions.mouse.clickXpos, (uint32_t)m_Interactions.mouse.clickYpos};

    ImageCopyBuffer buffer;
    buffer.buffer = m_PickBuffer;
    TextureDataLayout layout;
    layout.bytesPerRow = 256;
    layout.rowsPerImage = 1;
    layout.offset = 0;

    buffer.layout = layout;


    WGPUCommandBufferDescriptor cmdBufferDescriptor = {};
    cmdBufferDescriptor.nextInChain = nullptr;
    cmdBufferDescriptor.label = "CMD";
    m_RenderPass.end();
    
    m_CommandEncoder.copyTextureToBuffer(texture, buffer, {1, 1, 1});
    CommandBuffer cmdBuffer = m_CommandEncoder.finish(cmdBufferDescriptor);
    
   

    WGPUContext::queue.submit(1, &cmdBuffer);
    //
    bool done = false;


    auto handle = m_PickBuffer.mapAsync(MapMode::Read, 0, sizeof(glm::vec4), [&](BufferMapAsyncStatus status){

        saveTextureView("./texture.png", WGPUContext::device, m_PickerTextureView, 640, 480);
        if (status == BufferMapAsyncStatus::Success)
        {
            unsigned char * output = (unsigned char*)m_PickBuffer.getConstMappedRange(0, sizeof(glm::vec4));
            //std::cout << output[0] << " "<< output[1] <<" "<<output[2]<< std::endl;
            int r = output[0];
            int g = output[1];
            int b = output[2];
            int a = output[3];
            int index = (r | (g << 8) | (b << 16) | (b << 24)) - 1;
            SceneUI::Get()->SelectGeometry(index);
        }
        m_PickBuffer.unmap();
        done = true;
    });

    while(!done)
    {
        //WGPUContext::queue.submit(0, nullptr);
        WGPUContext::instance.processEvents();
    }
    //m_PickBuffer.unmap();

   

    cmdBuffer.release();
    m_CommandEncoder.release();
    m_RenderPass.release();
}