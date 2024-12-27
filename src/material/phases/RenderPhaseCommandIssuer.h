
#pragma once
#include <webgpu/webgpu.hpp>
#include "../../initiator/WGPUCommandSubmitter.h"
#include "BackendRenderPhase.h"

using namespace wgpu;
class RenderPhaseCommandIssuer
{
public:
    static void IssueCmd(const std::vector<std::shared_ptr<BackendRenderPhase>> &phases)
    {
        CommandEncoder encoder;
        for (auto phase: phases)
        {
            // runs in sequence.
            // multiple renderpass
            RenderPassEncoder renderPass = phase.get()->BeginRenderPass(encoder);
            /**
             *  renderPass code
             * 
            */
            renderPass.end();
            renderPass.release();
        }    
        CommandBufferDescriptor desc = {};
        CommandBuffer cmdBuffer = encoder.finish(desc);
        encoder.release();
        //WGPUContext::queue.submit(1, &cmdBuffer);
        WGPUCommandSubmitter::Get()->BufferCmd(cmdBuffer);
    }
};