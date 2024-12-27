#include "ShadowMapRendererCommand.h"
void ShadowMapRendererCommand::Render()
{

    // loop for each light and cascade

// for (int i = 0; i < lights.count ; i++)
    for (int j = 0; j < constants::MAX_CSM_LVL; j++)
    {
        Begin();
        m_ShadowMapRenderPass.SetCascade(j);
        RenderPassEncoder renderPass = m_ShadowMapRenderPass.BeginScreenRenderPass(m_CommandEncoder);
        auto & geos = Scene::GetInstance()->GetGeometries();

        for (auto &geo: geos)
        {
            UpdateModel(geo.get());
            //auto &phases = geo.get()->GetCurrentMaterial()->GetScreenPhases();
            auto &phases = ShadowMapCSMMaterial::Get()->GetScreenPhases();
            for (auto &phase: phases)
            {
                void *context[2] = { (void *)geo.get(), (void *)&j};
                phase.get()->RenderByRenderPass(renderPass, context);
            }
        }
        renderPass.end();
        renderPass.release();
        WGPUCommandSubmitter::Get()->BufferCmd(m_CommandEncoder);
    }
   
}