#pragma once
#include "../../shader/BaseComputePipeline.h"
#include "../../storages/StorageBuffer.h"
#include "../../shader/ComputeHelloWorldPipeline.h"

class ComputeRenderPhase
{
protected:
    BaseComputePipeline *m_ComputePipeline = nullptr;
    BindGroup m_BindGroup = nullptr;
    StorageBuffer m_InputBuffer;
    StorageBuffer m_OutputBuffer;
    StorageBuffer m_MapBuffer;

public:
    ComputeRenderPhase();
    virtual void Compute() = 0;
    virtual void CreateBindGroups() 
    {
        std::vector<BindGroupEntry> bindGroupEntries;
        auto computeBindGroupLayout = m_ComputePipeline->GetBindGroupLayout();
        auto computeBindGroupOptions = m_ComputePipeline->GetBindGroupOptions();

        BindGroupDescriptor bindGroupDesc{};


        bindGroupDesc.layout = computeBindGroupLayout;
        bindGroupDesc.entryCount = computeBindGroupOptions.size();
        bindGroupDesc.label = "computeBindGroup";

        int index = 0;
        for (auto & bindGroupOption: computeBindGroupOptions)
        {
            BindGroupEntry entry{};
            entry.binding = index++;
            entry.offset = 0;
            if (bindGroupOption.bindGroupType == BindGroupType::READ_ONLY_STORAGE) {
                entry.buffer = m_InputBuffer.GetBuffer();
            }
           
            if (bindGroupOption.bindGroupType == BindGroupType::STORAGE) {
                entry.buffer =m_OutputBuffer.GetBuffer();
            }
            
        }

        bindGroupDesc.entryCount = bindGroupEntries.size();
        bindGroupDesc.entries = bindGroupEntries.data();

        m_BindGroup = WGPUContext::device.createBindGroup(bindGroupDesc);
    }
};