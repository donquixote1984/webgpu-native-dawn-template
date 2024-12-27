#include <webgpu/webgpu.hpp>
#include "../data/Canvas.h"
#include "../geometry/Geometry.h"
#include "../material/phases/RayRenderPhase.h"
#include "../geometry/GeometryCreator.h"

using namespace wgpu;

class RayCanvasSimple
{
private:
    std::shared_ptr<Geometry> m_Canvas;
    RayRenderPhase m_RenderPhase;


public:
    RayCanvasSimple()
    {
        m_Canvas = GeometryCreator::Builder().get()->AddMesh(data::fullScreenCanvasVertices, data::canvasIndices, 4, 6, VertexDescriptor::VERTEX_BASE)
        ->Build();
    }

    static RayCanvasSimple* Get()
    {
        static RayCanvasSimple debugWindow;
        return &debugWindow;
    }

    void Render(RenderPassEncoder &renderPass)
    {
        void * context[1] = {(void*)m_Canvas.get()};
        m_RenderPhase.RenderByRenderPass(renderPass, context);
    }

    void AddTexture(std::shared_ptr<DiskTextureObject> texture)
    {
        m_RenderPhase.AddTexture(texture);
    }
};