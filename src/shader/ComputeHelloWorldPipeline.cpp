#include "ComputeHelloWorldPipeline.h"

ComputeHelloWorldPipeline::ComputeHelloWorldPipeline()
{
    m_Shader = Shader("resources/shaders/compute_hello_world.wgsl");
    uint32_t index = 0;

    m_ComputeBindGroupOptions.push_back({index++, BindGroupType::READ_ONLY_STORAGE,  "input"});
    m_ComputeBindGroupOptions.push_back({index++, BindGroupType::STORAGE, "output"});
}
void ComputeHelloWorldPipeline::CreateBindGroupLayout()
{
    BindGroupLayoutDescriptor computeBindGroupLayoutDesc{};
    computeBindGroupLayoutDesc.entryCount = m_ComputeBindGroupOptions.size();
    std::vector<BindGroupLayoutEntry> entries(m_ComputeBindGroupOptions.size());

        std::transform(m_ComputeBindGroupOptions.begin(), m_ComputeBindGroupOptions.end(), entries.begin(), [](ComputeBindGroupOptions & option){
        return option.CreateBindGroupLayoutEntry();
    });
    computeBindGroupLayoutDesc.entries = entries.data();

    m_ComputeBindGroupLayout = WGPUContext::device.createBindGroupLayout(computeBindGroupLayoutDesc);

}

void ComputeHelloWorldPipeline::CreatePipeline()
{
    m_ComputePipeline = WGPUContext::CreateComputePipeline(m_Shader, &m_ComputeBindGroupLayout);
}