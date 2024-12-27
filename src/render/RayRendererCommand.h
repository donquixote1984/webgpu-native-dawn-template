#pragma once
#include "RendererCommand.h"
#include "../passes/SceneRenderPass.h"
#include "../canvas/RayCanvasSimple.h"
#include "../Scene.h"
#include "../initiator/WGPUCommandSubmitter.h"
#include <chrono>
#include <thread>

class RayRendererCommand:  public RendererCommand
{
private:
    SceneRenderPass m_RayRenderPass; // hold final preview texture
    std::unique_ptr<QueueWorkDoneCallback> handle;
public:
    virtual void Render() override;
};