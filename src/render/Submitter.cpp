
#include "Submitter.h"

void Submitter::SubmitRenderPass()
{
        WGPUCommandBufferDescriptor cmdBufferDescriptor = {};
        cmdBufferDescriptor.nextInChain = nullptr;
        cmdBufferDescriptor.label = "CMD";
        m_RenderPass.end();
        m_RenderPass.release();
        CommandBuffer cmdBuffer = m_CommandEncoder.finish(cmdBufferDescriptor);
        m_CommandEncoder.release();
        WGPUContext::queue.submit(1, &cmdBuffer);
        //
        cmdBuffer.release();
}

RenderPassDepthStencilAttachment Submitter::CreateDepthAttachment(TextureView depthView)
{
    RenderPassDepthStencilAttachment depthStencilAttachment;
    depthStencilAttachment.view = depthView;
    depthStencilAttachment.depthClearValue = 1.0f;
		// Operation settings comparable to the color attachment
    depthStencilAttachment.depthLoadOp = LoadOp::Clear;
    depthStencilAttachment.depthStoreOp = StoreOp::Store;
    // we could turn off writing to the depth buffer globally here
    depthStencilAttachment.depthReadOnly = false;
    depthStencilAttachment.stencilClearValue = 0;
    depthStencilAttachment.stencilLoadOp = LoadOp::Undefined;
    depthStencilAttachment.stencilStoreOp = StoreOp::Undefined;
    depthStencilAttachment.stencilReadOnly = true;
    return depthStencilAttachment;
}

RenderPassColorAttachment Submitter::CreateColorAttachment(TextureView colorView)
{
    RenderPassColorAttachment renderpassColorAttachmentDesc = {};
    renderpassColorAttachmentDesc.view = colorView;
    renderpassColorAttachmentDesc.resolveTarget = nullptr;
    renderpassColorAttachmentDesc.loadOp = WGPULoadOp_Clear;
    renderpassColorAttachmentDesc.storeOp = WGPUStoreOp_Store;
    renderpassColorAttachmentDesc.clearValue = WGPUColor{ 0.0, 0.0, 0.0, 1.0 };
    renderpassColorAttachmentDesc.depthSlice = WGPU_DEPTH_SLICE_UNDEFINED;
    return renderpassColorAttachmentDesc;
}