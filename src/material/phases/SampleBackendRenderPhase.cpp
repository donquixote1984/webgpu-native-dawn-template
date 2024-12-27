#include "SampleBackendRenderPhase.h"

SampleBackendRenderPhase::SampleBackendRenderPhase()
{
    m_DepthTexture = WGPUContext::CreateScreenDepth();
    m_Pipeline = SampleColoredPipeline::Get();
    CreateBindGroups();
}

void SampleBackendRenderPhase::CreateBindGroups()
{
    CreateUniformBindGroup();
}