#pragma once
#include <vector>
#include <webgpu/webgpu.hpp>
#include "WGPUContext.h"

using namespace wgpu;
class WGPUCommandSubmitter
{
private:
    std::vector<CommandBuffer> m_CmdBuffers;
public:
    void BufferCmd(CommandEncoder &encoder)
    {
        WGPUCommandBufferDescriptor cmdBufferDescriptor = {};
        cmdBufferDescriptor.nextInChain = nullptr;
        cmdBufferDescriptor.label = "CMD";
        CommandBuffer cmdBuffer = encoder.finish(cmdBufferDescriptor);
        encoder.release();
        encoder = nullptr;
        BufferCmd(cmdBuffer);
    }
    void BufferCmd(CommandBuffer buffer)
    {
        m_CmdBuffers.push_back(buffer);
    }

    void Submit()
    {
        WGPUContext::queue.submit(m_CmdBuffers.size(), m_CmdBuffers.data());

        for (auto cmd: m_CmdBuffers)
        {
            cmd.release();
        }
        m_CmdBuffers.clear();
    }
    static WGPUCommandSubmitter * Get()
    {
        static WGPUCommandSubmitter submitter;
        return &submitter;
    }
};