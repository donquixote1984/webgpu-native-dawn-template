#pragma once
#include <webgpu/webgpu.hpp>
#include <memory>
#include "../initiator/WGPUContext.h"
#include "../geometry/Geometry.h"
#include "../data/Canvas.h"
#include "../geometry/GeometryCreator.h"
#include "../shader/DebugWindowPipeline.h"
#include "../material/phases/DebugWindowRenderPhase.h"

using namespace wgpu;
class DebugWindow
{
private:
    std::shared_ptr<Geometry> m_Geometry;
    DebugWindowRenderPhase m_RenderPhase;
public:

    DebugWindow()
    {
        m_Geometry = GeometryCreator::Builder().get()->AddMesh(data::topRightCanvasVertices, data::canvasIndices, 4, 6, VertexDescriptor::VERTEX_BASE)
        ->Build();
    }

    ~DebugWindow()
    {}

    static DebugWindow * Get()
    {
        static DebugWindow debugWindow;
        return &debugWindow;
    }
    void Render(RenderPassEncoder &renderPass)
    {
        void * context[1] = {(void*)m_Geometry.get()};
        m_RenderPhase.RenderByRenderPass(renderPass, context);
    }

    void SetWindowTextureView(TextureView textureView)
    {
        m_RenderPhase.SetWindowTextureView(textureView);
    }
};