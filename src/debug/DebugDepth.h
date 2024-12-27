#pragma once
#include <webgpu/webgpu.hpp>
#include <memory>
#include "../initiator/WGPUContext.h"
#include "../geometry/Geometry.h"
#include "../data/Canvas.h"
#include "../geometry/GeometryCreator.h"
#include "../material/phases/DebugDepthRenderPhase.h"

using namespace wgpu;
class DebugDepth
{
private:
    std::shared_ptr<Geometry> m_Geometry;
    DebugDepthRenderPhase m_RenderPhase;
public:

    DebugDepth()
    {
        m_Geometry = GeometryCreator::Builder().get()->AddMesh(data::quarterCanvasVertices, data::canvasIndices, 4, 6, VertexDescriptor::VERTEX_BASE)
        ->Build();
    }

    ~DebugDepth()
    {}

    static DebugDepth * Get()
    {
        static DebugDepth debugDepth;
        return &debugDepth;
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