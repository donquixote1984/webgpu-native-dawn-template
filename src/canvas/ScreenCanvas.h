#pragma once
#include <webgpu/webgpu.hpp>
#include "../geometry/Geometry.h"
#include "../geometry/GeometryCreator.h"
#include "../data/Canvas.h"
#include "../material/phases/DebugWindowRenderPhase.h"

using namespace wgpu;

class ScreenCanvas
{
private:
    std::shared_ptr<Geometry> m_Canvas;
    DebugWindowRenderPhase m_RenderPhase;
public:
    ScreenCanvas()
    {
        m_Canvas = GeometryCreator::Builder().get()->AddMesh(data::fullScreenCanvasVertices, data::canvasIndices, 4, 6, VertexDescriptor::VERTEX_BASE)
        ->Build();
    }
    static ScreenCanvas* Get()
    {
        static ScreenCanvas debugWindow;
        return &debugWindow;
    }
    void Render(RenderPassEncoder &renderPass)
    {
        void * context[1] = {(void*)m_Canvas.get()};
        m_RenderPhase.RenderByRenderPass(renderPass, context);
    }

    void SetWindowTextureView(TextureView textureView)
    {
        m_RenderPhase.SetWindowTextureView(textureView);
    }
};