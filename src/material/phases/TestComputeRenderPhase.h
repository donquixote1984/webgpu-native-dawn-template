#pragma once
#include <vector>
#include "../../initiator/WGPUContext.h"
#include "ComputeRenderPhase.h"

class TestComputeRenderPhase: public ComputeRenderPhase
{
public:
    virtual void Compute() override
    {
        int count = 100;
        std::vector<float> input;
        for (int i = 0; i < count; ++i) {
            input.push_back(0.1f * i);
	    }

        int bufferSize =  input.size() * sizeof(float);
        WGPUContext::queue.writeBuffer(m_InputBuffer.GetBuffer(), 0, input.data(), bufferSize);

        CommandEncoderDescriptor encoderDesc = Default;
        CommandEncoder encoder = WGPUContext::device.createCommandEncoder(encoderDesc);

        // Create compute pass
        ComputePassDescriptor computePassDesc;
        computePassDesc.timestampWrites = nullptr;
        ComputePassEncoder computePass = encoder.beginComputePass(computePassDesc);
        computePass.setPipeline(m_ComputePipeline->GetPipeline());
        computePass.setBindGroup(0, m_BindGroup, 0, nullptr);
        uint32_t invocationCount = count;
        uint32_t workgroupSize = 32;

        uint32_t workgroupCount = (invocationCount + workgroupSize - 1) / workgroupSize;
        computePass.dispatchWorkgroups(workgroupCount, 1, 1);
        computePass.end();

	    // Before encoder.finish
	    encoder.copyBufferToBuffer(m_OutputBuffer.GetBuffer(), 0, m_MapBuffer.GetBuffer(), 0, bufferSize);
        CommandBuffer commands = encoder.finish(CommandBufferDescriptor{});
	    WGPUContext::queue.submit(commands);


        bool done = false;
        auto handle = m_MapBuffer.GetBuffer().mapAsync(MapMode::Read, 0, bufferSize, [&](BufferMapAsyncStatus status) {
            if (status == BufferMapAsyncStatus::Success) {
                const float* output = (const float*)m_MapBuffer.GetBuffer().getConstMappedRange(0, bufferSize);
                for (int i = 0; i < input.size(); ++i) {
                    std::cout << "input " << input[i] << " became " << output[i] << std::endl;
                }
                m_MapBuffer.GetBuffer().unmap();
            }
            done = true;
        });

        while (!done) {
            // Checks for ongoing asynchronous operations and call their callbacks if needed
            WGPUContext::instance.processEvents();
        }
    }
};