#pragma once
#include "RenderPhase.h"

class BackendRenderPhase: public RenderPhase
{
protected:
    RenderPhaseType type = RenderPhaseType::BACKEND;
    Texture m_ColorTexture = nullptr;
    Texture m_DepthTexture = nullptr;
public:
    virtual RenderPassEncoder BeginRenderPass(CommandEncoder &encoder) = 0;
    ~BackendRenderPhase()
    {
        WGPUContext::ReleaseIfNotNull(m_ColorTexture);
        WGPUContext::ReleaseIfNotNull(m_DepthTexture);
    }
};