#pragma once
#include <webgpu/webgpu.hpp>
#include "../initiator/WGPUContext.h"
using namespace wgpu;
class Submitter
{
protected:
    CommandEncoder m_CommandEncoder = nullptr;
    RenderPassEncoder m_RenderPass = nullptr;
    std::string m_Name;
    RenderPassDepthStencilAttachment CreateDepthAttachment(TextureView depthView);
    RenderPassColorAttachment CreateColorAttachment(TextureView colorView);
public:
    void _BeginRenderPass()
    {
        CommandEncoderDescriptor desc = {};
        desc.label = m_Name.c_str();
        m_CommandEncoder = WGPUContext::device.createCommandEncoder();
    }

    virtual RenderPassEncoder BeginRenderPass() = 0;
   
    virtual void SubmitRenderPass();
};