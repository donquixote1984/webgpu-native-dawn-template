#pragma once
#include "../passes/SceneRenderPass.h"
#include "RendererCommand.h"
#include "../Scene.h"
#include "../initiator/WGPUCommandSubmitter.h"
#include <chrono>
#include <thread>

using namespace std::chrono_literals;
class SceneRendererCommand: public RendererCommand
{
private:
    SceneRenderPass m_SceneRenderPass; // hold final preview texture
    std::unique_ptr<QueueWorkDoneCallback> handle;
public:
    virtual void Render() override;
};