#pragma once
#include <vector>
#include <webgpu/webgpu.hpp>
#include "../initiator/WGPUContext.h"
#include "../base/Vertex.h"
#include "../base/Constants.h"
#include "../enums/BindGroupType.h"
#include "PipelineOptions.h"
#include "Shader.h"

using namespace wgpu;

class BasePipeline
{
protected:
    Shader m_Shader;
    BindGroupLayout m_UniformBindGroupLayout = nullptr;
    BindGroupLayout m_TextureBindGroupLayout = nullptr;
    BindGroupLayout m_SamplerBindGroupLayout = nullptr;

    RenderPipeline m_RenderPipeline = nullptr;
    uint16_t m_Stride = 0;
    std::vector<VertexAttribute> m_Attributes;
    std::vector<BindGroupOptions> m_TextureBindGroupOptions;
    std::vector<BindGroupOptions> m_UniformBindGroupOptions;
    std::vector<BindGroupOptions> m_SamplerBindGroupOptions;

    std::vector<UniformBuffer *> m_UniformBuffers;
    BindGroup m_UniformBindGroup = nullptr;
    BindGroup m_TextureBindGroup = nullptr;
    BindGroup m_SamplerBindGroup = nullptr;
public:
    BasePipeline(){}
    virtual void CreateBindGroupLayout() = 0;
    virtual void CreatePipeline() = 0;
    void Create();

    const BindGroupLayout & GetUniformBindGroupLayout() const
    {
        return m_UniformBindGroupLayout;
    }

    const BindGroupLayout & GetTextureBindGroupLayout() const
    {
        return m_TextureBindGroupLayout;
    }

    const BindGroupLayout & GetSamplerBindGroupLayout() const
    {
        return m_SamplerBindGroupLayout;
    }

    const std::vector<BindGroupOptions> & GetUniformBindGroupOptions() const
    {
        return m_UniformBindGroupOptions;
    }

    const std::vector<BindGroupOptions> & GetTextureBindGroupOptions() const
    {
        return m_TextureBindGroupOptions;
    }

    const std::vector<BindGroupOptions> & GetSamplerBindGroupOptions() const
    {
        return m_SamplerBindGroupOptions;
    }


    RenderPipeline GetRenderPipeline()
    {
        return m_RenderPipeline;
    }
    
    uint8_t GetDynamicOffsetCount()
    {
        int count = 0;
        for (auto & option: m_UniformBindGroupOptions)
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
        for (auto & option: m_UniformBindGroupOptions)
        {
            if (option.dynamic)
            {
                strides.push_back(UniformBufferCreator::CalculateStride(option.size));
            }
        }

        return strides;
    }

    UniformBuffer** GetUniformBuffers(size_t &size)
    {
        size = m_UniformBuffers.size();
        return m_UniformBuffers.data();
    }


};