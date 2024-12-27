#pragma once
#include "RendererCommand.h"
#include <webgpu/webgpu.hpp>
#include "../Scene.h"
#include "../initiator/WGPUContext.h"
#include "../uniforms/UniformBuffer.h"
#include "../uniforms/ModelUniform.h"
#include "../geometry/Geometry.h"
#include "../ui/PickerPipeline.h"
#include "../material/PickerMaterial.h"
#include "../uniforms/PickerUniform.h"
#include "../passes/PickerRenderPass.h"
#include "../initiator/WGPUCommandSubmitter.h"
#include "../SceneUI.h"
#include <memory>

using namespace wgpu;
class PickRendererCommand: public RendererCommand
{
private:
    PickerRenderPass m_PickRenderPass;
    std::unique_ptr<BufferMapCallback> handle;
public:
    PickRendererCommand() {}
    virtual void Render() override
    {
        //m_PickRenderPass.Render(m_CommandEncoder);
        Begin();
        RenderPassEncoder renderPass = m_PickRenderPass.BeginScreenRenderPass(m_CommandEncoder);
        auto & geos = Scene::GetInstance()->GetGeometries();
        for (auto &geo: geos)
        {
            UpdateModel(geo.get());
            //auto &phases = geo.get()->GetCurrentMaterial()->GetScreenPhases();
            auto &phases = PickerMaterial::Get()->GetScreenPhases();
            for (auto &phase: phases)
            {
                void *context[1] = { (void *)geo.get()};
                phase.get()->RenderByRenderPass(renderPass, context);
            }
        }
        renderPass.end();
        renderPass.release();
        ImageCopyTexture texture;
        texture.texture = m_PickRenderPass.GetTexture();
        auto &i = Scene::GetInstance()->GetInteractions();
        texture.origin = {(uint32_t)i.mouse.clickXpos, (uint32_t)i.mouse.clickYpos};
        if (i.mouse.clickXpos > 0) {

         std::cout << texture.origin.x << "  " << texture.origin.y << std::endl;
        }
        ImageCopyBuffer buffer;
        buffer.buffer = m_PickRenderPass.GetBuffer();
        TextureDataLayout layout;
        layout.bytesPerRow = 256;
        layout.rowsPerImage = 1;
        layout.offset = 0;

        buffer.layout = layout;

        m_CommandEncoder.copyTextureToBuffer(texture, buffer, {1, 1, 1});
        WGPUCommandSubmitter::Get()->BufferCmd(m_CommandEncoder);
        //WGPUCommandSubmitter::Get()->Submit();

    }
    virtual void PostCommandSubmit() override;
    PickerRenderPass & GetRenderPass() 
    {
        return m_PickRenderPass;
    }
};