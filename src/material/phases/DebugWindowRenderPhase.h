#pragma once
#include "ScreenRenderPhase.h"
#include "../../shader/DebugWindowPipeline.h"
#include "../../textures/ScreenTextureObject.h"
class DebugWindowRenderPhase: public ScreenRenderPhase
{
protected:
    TextureView m_TextureView = nullptr;
public:
    DebugWindowRenderPhase();
    virtual void RenderByRenderPass(RenderPassEncoder &renderPass, void ** context) override;
    virtual void CreateBindGroups() override;
    virtual void CreateTextureBindGroup();
    void CreateSamplerBindGroup();

    void SetWindowTextureView(TextureView textureView)
    {
        m_TextureView = textureView;
        CreateBindGroups();
    }
};