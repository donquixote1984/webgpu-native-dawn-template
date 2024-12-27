#pragma once
#include <webgpu/webgpu.hpp>
#include <vector>
#include <functional>
#include "Shader.h"
#include "PipelineOptions.h"
#include "../base/Vertex.h"

using namespace wgpu;

struct Pipeline
{
    
    RenderPipeline pipeline = nullptr;
    //  BindGroup bindGroup = nullptr;
    std::vector<BindGroupOptions> options;

    Pipeline() {}
    Pipeline(RenderPipeline x): pipeline(x) {}
    //  Pipeline(RenderPipeline x, BindGroup y): pipeline(x), bindGroup(y) {}
    Pipeline(RenderPipeline x, std::vector<BindGroupOptions> y): pipeline(x), options(y) {}
    ~Pipeline();

    void Release();

    uint8_t GetDynamicOffsetCount()
    {
        int count = 0;
        for (auto & option: options)
        {
            if (option.dynamic)
            {
                count += 1;
            }
        }
        return count;
    }

    std::vector<uint16_t> GetDynamicOffsetStrides()
    {
        std::vector<uint16_t> strides;
        for (auto & option: options)
        {
            if (option.dynamic)
            {
                strides.push_back(UniformBufferCreator::CalculateStride(option.size));
            }
        }

        return strides;
    }
};
