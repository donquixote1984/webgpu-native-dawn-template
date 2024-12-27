#pragma once
#include <webgpu/webgpu.hpp>
#include "RendererCommand.h"
#include "../Scene.h"
#include "../initiator/WGPUContext.h"
#include "../UI.h"
#include "../initiator/WGPUCommandSubmitter.h"
#include "../debug/DebugWindow.h"
#include "../debug/DebugShadow.h"
#include "../debug/DebugDepth.h"
#include "../canvas/ScreenCanvas.h"



using namespace wgpu;
class Geometry;
class CompositeRendererCommand: public RendererCommand
{
private:
    Texture m_DepthTexture;
    DebugWindow m_DebugWindow;
    //RenderPassEncoder m_RenderPass = nullptr;
public:
    CompositeRendererCommand();
    RenderPassEncoder CreateSceneRenderPass();
    RenderPassEncoder CreateSceneRenderPassOverlay();
    RenderPassEncoder CreateDebugRenderPass();
    void RenderUI();
    void RenderDebugWindow();
    void Submit();

    void Composite();
    virtual void Render() override
    {
        Begin(); //commandEncoder;
       // CreateSceneRenderPass();
        //RenderPostProcessing();
        // RenderDebugWindow();
        Composite();
        //RenderDebugWindow();
        RenderUI();
        Submit();
    }
};