#include "BaseComputePipeline.h"
void BaseComputePipeline::Create()
{
    CreateBindGroupLayout();
    CreatePipeline();
}
BaseComputePipeline::~BaseComputePipeline()
{
    WGPUContext::ReleaseIfNotNull(m_ComputePipeline);
    
}