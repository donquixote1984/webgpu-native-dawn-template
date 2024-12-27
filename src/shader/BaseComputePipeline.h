#pragma once
#include <vector>
#include <webgpu/webgpu.hpp>
#include "../initiator/WGPUContext.h"
#include "../base/Constants.h"
#include "../enums/BindGroupType.h"
#include "PipelineOptions.h"
#include "Shader.h"

class BaseComputePipeline
{
protected:
    Shader m_Shader;
    std::vector<ComputeBindGroupOptions>  m_ComputeBindGroupOptions;
    BindGroupLayout m_ComputeBindGroupLayout;
    ComputePipeline m_ComputePipeline = nullptr;
public:
    BaseComputePipeline() {}
    ~BaseComputePipeline();
    const ComputePipeline & GetPipeline() const
    {
        return m_ComputePipeline;
    }
    virtual void CreateBindGroupLayout() = 0;
    virtual void CreatePipeline() = 0;
    void Create();

    BindGroupLayout GetBindGroupLayout()
    {
        return m_ComputeBindGroupLayout;
    }

    const std::vector<ComputeBindGroupOptions> & GetBindGroupOptions() const
    {
        return m_ComputeBindGroupOptions;
    }

};