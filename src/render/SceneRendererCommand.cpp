#include "SceneRendererCommand.h"

void SceneRendererCommand::Render()
{
    Begin(); // commandEncoder;
    RenderPassEncoder renderPass = m_SceneRenderPass.BeginScreenRenderPass(m_CommandEncoder);
    auto & geos = Scene::GetInstance()->GetGeometries();
    for (auto &geo: geos)
    {
        UpdateModel(geo.get());
        auto &phases = geo.get()->GetCurrentMaterial()->GetScreenPhases();
        for (auto &phase: phases)
        {
            void *context[1] = { (void *)geo.get()};
            phase.get()->RenderByRenderPass(renderPass, context);
        }
    }
    renderPass.end();
    renderPass.release();
    renderPass = nullptr;
    WGPUCommandSubmitter::Get()->BufferCmd(m_CommandEncoder);
    WGPUCommandSubmitter::Get()->Submit();

    bool workDone = false;
    handle = WGPUContext::queue.onSubmittedWorkDone([&](QueueWorkDoneStatus status){
        workDone = true;
        this->m_SceneRenderPass.SendToScreen();
    });

    while(!workDone)
    {
        WGPUContext::instance.processEvents();
        std::this_thread::sleep_for(1ms);
    }
    this->m_SceneRenderPass.SendToDebugDepth();
}