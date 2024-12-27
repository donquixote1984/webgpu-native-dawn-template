#include "CompositeRendererCommand.h"
#include "../geometry/Geometry.h"

CompositeRendererCommand::CompositeRendererCommand()
{
    m_DepthTexture = WGPUContext::CreateScreenDepth();
}
void CompositeRendererCommand::Submit()
{
    WGPUCommandSubmitter::Get()->BufferCmd(m_CommandEncoder);
    WGPUCommandSubmitter::Get()->Submit();
}
RenderPassEncoder CompositeRendererCommand::CreateSceneRenderPass()
{
    TextureView depthView = WGPUContext::CreateDepthView2D(m_DepthTexture);
    RenderPassDescriptor desc = WGPUContext::CreateSurfaceRenderPassDesc(depthView);
    auto att1 = WGPUContext::CreateSurfaceColorAttachment();
    auto att2 = WGPUContext::CreateDepthAttachment(depthView);
    desc.colorAttachments = &att1;
    desc.depthStencilAttachment = &att2;
    RenderPassEncoder renderPass = m_CommandEncoder.beginRenderPass(desc);
    return renderPass;
}

RenderPassEncoder CompositeRendererCommand::CreateDebugRenderPass()
{
    TextureView depthView = WGPUContext::CreateDepthView2D(m_DepthTexture);
    RenderPassDescriptor desc = WGPUContext::CreateSurfaceRenderPassDesc(depthView);
    auto att1 = WGPUContext::CreateSurfaceColorOverlayAttachment();
    auto att2 = WGPUContext::CreateDepthAttachment(depthView);
    desc.colorAttachments = &att1;
    desc.depthStencilAttachment = &att2;
    
    RenderPassEncoder renderPass = m_CommandEncoder.beginRenderPass(desc);
    return renderPass;
}


RenderPassEncoder CompositeRendererCommand::CreateSceneRenderPassOverlay()
{
    TextureView depthView = WGPUContext::CreateDepthView2D(m_DepthTexture);
    RenderPassDescriptor desc = WGPUContext::CreateSurfaceRenderPassDesc(depthView);
    auto att1 = WGPUContext::CreateSurfaceColorOverlayAttachment();
    auto att2 = WGPUContext::CreateDepthAttachment(depthView);
    desc.colorAttachments = &att1;
    desc.depthStencilAttachment = &att2;
    RenderPassEncoder renderPass = m_CommandEncoder.beginRenderPass(desc);
    return renderPass;
}


/*
void CompositeRendererCommand::RenderScene()
{
    Begin(); // commandEncoder;
    RenderPassEncoder renderPass = CreateSceneRenderPass();
    auto & geos = Scene::GetInstance()->GetGeometries();
    for (auto &geo: geos)
    {
        UpdateModel(geo.get());
        auto &phases = geo.get()->GetCurrentMaterial()->GetScreenPhases();
        for (auto &phase: phases)
        {
            phase.get()->RenderByRenderPass(renderPass, (void *)geo.get());
        }
    }
    renderPass.end();
    renderPass.release();
    renderPass = nullptr;
}
*/

void CompositeRendererCommand::Composite()
{
    RenderPassEncoder renderPass = CreateSceneRenderPass();
    ScreenCanvas::Get()->Render(renderPass);
    renderPass.end();
    renderPass.release();
    renderPass = nullptr;
}

void CompositeRendererCommand::RenderUI()
{
    RenderPassEncoder renderPass = CreateSceneRenderPassOverlay();
    UI::Get()->Update(renderPass);
    renderPass.end();
    renderPass.release();
    renderPass = nullptr;
}

void CompositeRendererCommand::RenderDebugWindow()
{
    RenderPassEncoder renderPass = CreateSceneRenderPassOverlay();
    DebugShadow::Get()->Render(renderPass);
    renderPass.end();
    renderPass.release();
    renderPass = nullptr;
}