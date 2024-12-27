#pragma once
#include <webgpu/webgpu.hpp>
#include <glm/glm.hpp>
#include "../initiator/WGPUContext.h"
#include "../uniforms/UniformBuffer.h"

#include "../base/Constants.h"
using namespace wgpu;
class Picker
{
private:
    
    Buffer m_PickerReadBuffer;
    Buffer m_PickerUniformBuffer;
    RenderPipeline m_PickerPipeline;
    BindGroup m_PickerBindGroup;

public:    Picker();

    BindGroup GetBindGroup(){
        return m_PickerBindGroup;
    }
    Buffer GetPickerBuffer()
    {
        return m_PickerUniformBuffer;
    }
    RenderPipeline GetPipeline()
    {
        return m_PickerPipeline;
    }
    static Picker * Get()
    {
        static Picker picker;
        return &picker;
    }
};