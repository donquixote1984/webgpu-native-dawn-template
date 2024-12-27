#include "ComputeRenderPhase.h"

ComputeRenderPhase::ComputeRenderPhase()
{
    m_InputBuffer.m_Buffer = WGPUContext::device.createBuffer(StorageBuffer::CreateDesc(1024, "storage input buffer"));
    m_OutputBuffer.m_Buffer = WGPUContext::device.createBuffer(StorageBuffer::CreateDesc(1024, "storage output buffer"));
    m_MapBuffer.m_Buffer = WGPUContext::device.createBuffer(StorageBuffer::CreateMapDesc(1024, "storage map buffer"));
    m_ComputePipeline = ComputeHelloWorldPipeline::Get();
}