#pragma once
#include "BaseRenderPass.h"
#include "../canvas/ScreenCanvas.h"
#include "../debug/DebugWindow.h"
#include "../debug/DebugDepth.h"

class SceneRenderPass: public BaseRenderPass
{
private:
public:
    SceneRenderPass()
    {
        m_ColorTexture = WGPUContext::CreateScreenTexture();
        m_DepthTexture = WGPUContext::CreateScreenDepth();
    }

    TextureView GetTextureView()
    {
        return WGPUContext::CreateTextureView2D(m_ColorTexture);
    }
    void SendToScreen()
    {
        ScreenCanvas::Get()->SetWindowTextureView(GetTextureView());
    }

    void SendToDebugWindow()
    {
        DebugWindow::Get()->SetWindowTextureView(WGPUContext::CreateDepthView2D(m_DepthTexture));
    }

    void SendToDebugDepth()
    {
        DebugDepth::Get()->SetWindowTextureView(WGPUContext::CreateDepthView2D(m_DepthTexture));
    }
};