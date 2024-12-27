#pragma once
#include <webgpu/webgpu.hpp>
#include "Submitter.h"

using namespace wgpu;
class RenderPassSubmitter: public Submitter
{
protected:
    Texture m_DepthTexture = nullptr;
    TextureView m_TargetView = nullptr;
    TextureView m_DepthView = nullptr;
    void CreateDepthTextureView();

    RenderPassSubmitter()
    {
        CreateDepthTextureView();
    }
public:

    virtual RenderPassEncoder BeginRenderPass() override;

    static RenderPassSubmitter * Get()
    {
        static RenderPassSubmitter submitter;
        return &submitter;
    }
};