#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <webgpu/webgpu.hpp>
#include "Shader.h"
#include "../enums/BindGroupType.h"
#include "../base/Vertex.h"
#include "../uniforms/UniformBuffer.h"
#include "../uniforms/ViewProjectionUniform.h"
#include "../uniforms/ModelUniform.h"
#include "../uniforms/LightUniform.h"
#include "../light/PointLight.h"
#include "../uniforms/CountUniform.h"

using namespace wgpu;

struct ComputeBindGroupOptions {
    uint32_t index;
    BindGroupType bindGroupType = BindGroupType::NONE;
    std::string label = "";
    const BindGroupLayoutEntry CreateBindGroupLayoutEntry() const
    {
        BindGroupLayoutEntry bindingLayout = Default;
        bindingLayout.binding = index;
        bindingLayout.visibility = ShaderStage::Compute;
        if (bindGroupType == BindGroupType::READ_ONLY_STORAGE) {
            bindingLayout.buffer.type = BufferBindingType::ReadOnlyStorage;
        } else {
            bindingLayout.buffer.type = BufferBindingType::Storage;
        }
        return bindingLayout;
    }
};


struct BindGroupOptions
{
    uint32_t index;
    BindGroupType bindGroupType = BindGroupType::NONE;
    UniformBufferType uniformBufferType = UniformBufferType::NONE;
    size_t size = 0;
    bool dynamic = false;
    std::string label = "";

    const BindGroupLayoutEntry CreateBindGroupLayoutEntry() const
    {
        BindGroupLayoutEntry bindingLayout = Default;
        bindingLayout.binding = index;
        if (bindGroupType == BindGroupType::BUFFER) 
        {
            bindingLayout.visibility = ShaderStage::Vertex | ShaderStage::Fragment;
            bindingLayout.buffer.type = BufferBindingType::Uniform;
            bindingLayout.buffer.minBindingSize = size;
            bindingLayout.buffer.hasDynamicOffset = dynamic;
        } else if (bindGroupType == BindGroupType::TEXTURE)
        {
            bindingLayout.visibility = ShaderStage::Fragment;
            bindingLayout.texture.sampleType =  TextureSampleType::Float;
            bindingLayout.texture.viewDimension = TextureViewDimension::_2D;
        } else if (bindGroupType == BindGroupType::DEPTH)
        {
            bindingLayout.visibility = ShaderStage::Fragment;
            bindingLayout.texture.sampleType =  TextureSampleType::Depth;
            bindingLayout.texture.viewDimension = TextureViewDimension::_2D;
        } else if (bindGroupType == BindGroupType::DEPTH_ARRAY)
        {
            bindingLayout.visibility = ShaderStage::Fragment;
            bindingLayout.texture.sampleType =  TextureSampleType::Depth;
            bindingLayout.texture.viewDimension = TextureViewDimension::_2DArray;
        }
        else if(bindGroupType == BindGroupType::SAMPLER)
        {
            bindingLayout.visibility = ShaderStage::Fragment;
            bindingLayout.sampler.type = SamplerBindingType::Filtering;
        }

        return bindingLayout;
    }

    const BindGroupEntry CreateUniformBindGroupEntry() const
    {
        BindGroupEntry binding{};
        binding.binding = index;
        binding.buffer = UniformBuffer::GetByType(uniformBufferType)->GetBuffer();
        binding.offset = 0;
        binding.size = size;
        return binding;
    }

    const BindGroupEntry CreateSamplerBindGroupEntry() const
    {
        BindGroupEntry binding{};
        binding.binding = index;
        binding.buffer = UniformBuffer::GetByType(uniformBufferType)->GetBuffer();
        binding.offset = 0;
        binding.size = size;
        return binding;
    }
};


struct PipelineOptions {
    Shader shader;
    std::vector<VertexAttribute> vertexAttribs;
    uint16_t stride;
    std::vector<BindGroupOptions> bindGroupOptions;
    std::vector<BindGroupLayoutEntry> GetLayoutEntries()
    {
        std::vector<BindGroupLayoutEntry> entries;
        //std::transform(bindGroupOptions.begin(), bindGroupOptions.end(), entries.begin(), [](BindGroupOptions &option){
        //    return option.CreateBindGroupLayout();
        //});
        for(const BindGroupOptions & option : bindGroupOptions)
        {
            entries.push_back(option.CreateBindGroupLayoutEntry());
        }
        return entries;
    }

    uint8_t GetDynamicOffsetCount()
    {
        int offsetCount = 0;
        for (const BindGroupOptions & option: bindGroupOptions)
        {
            if (option.dynamic)
            {
                offsetCount += 1;
            }
        }

        return offsetCount;
    }
};