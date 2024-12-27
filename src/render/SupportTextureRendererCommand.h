#pragma once
#include <chrono>
#include <thread>
#include "RendererCommand.h"
#include "PickRendererCommand.h"
#include "ShadowMapRendererCommand.h"
#include "../passes/SceneRenderPass.h"
#include "../initiator/WGPUContext.h"
#include "../initiator/WGPUCommandSubmitter.h"

using namespace std::chrono_literals;
class SupportTextureRendererCommand: public RendererCommand
{
/**
 * picker
 * reflection
 * shadow map
 * 
*/
private:
    PickRendererCommand m_PickRendererCommand;
    ShadowMapRendererCommand m_ShadowMapRendererCommand;
    SceneRenderPass m_SceneRenderPass; // hold preview texture
public:
    virtual void Render() override;
    static void OnSubmitDone(WGPUQueueWorkDoneStatus, void *);
    
};