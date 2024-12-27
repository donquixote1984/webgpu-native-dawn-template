
#include "SupportTextureRendererCommand.h"
void SupportTextureRendererCommand::OnSubmitDone(WGPUQueueWorkDoneStatus status, void * userdata)
{
    (*(bool *)userdata) = true;

}
void SupportTextureRendererCommand::Render()
{
    // all the cmd runs at the same time.
    m_PickRendererCommand.Render(); // just submitted the cmd
    m_ShadowMapRendererCommand.Render(); // just submitted the cmd,,

    // submit other command...
    // submit other command...
    // submit other command...
    // submit other command...
    // submit other command...
    // submit other command...
    

    //  batch submitting the cmds
    WGPUCommandSubmitter::Get()->Submit();
    m_PickRendererCommand.PostCommandSubmit();
    m_ShadowMapRendererCommand.PostCommandSubmit();

    bool workDone = false;

    //QueueWorkDoneCallback callback = SceneRendererCommand::OnSubmitDone;

    //WGPUContext::queue.onSubmittedWorkDone(callback);
    //info.userdata = nullptr;
    //info.callback = SceneRendererCommand::OnSubmitDone;
    //WGPUContext::queue.onSubmittedWorkDone(info);

    // queue.onSubmittedWorkDone(info) just does not work for now;
    wgpuQueueOnSubmittedWorkDone(WGPUContext::queue, SupportTextureRendererCommand::OnSubmitDone, &workDone);
    while(!workDone)
    {
        WGPUContext::instance.processEvents();
        std::this_thread::sleep_for(1ms);
    }

    // no need to create texture view every frame.
    //this->m_ShadowMapRendererCommand.SendToDebugWindow(); // out put the depth texture
}

