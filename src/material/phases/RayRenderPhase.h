#pragma once 
#include "ScreenRenderPhase.h"
#include "../../shader/RaytracingSimplePipeline.h"
#include "DebugWindowRenderPhase.h"
#include "../../shadow/SceneShadowMapCSMTexture.h"
#include "../../textures/DiskTextureObject.h"
class RayRenderPhase: public DebugWindowRenderPhase
{
protected:
    RenderPassEncoder m_RenderPass;
    RenderPhaseType type = RenderPhaseType::SCREEN;
    std::vector<std::shared_ptr<DiskTextureObject>> m_Textures;
    bool m_hasBindGroupCreated = false;
public:
    RayRenderPhase();
    virtual void RenderByRenderPass(RenderPassEncoder &renderPass, void ** context) override;
    virtual void CreateTextureBindGroup() override;
    void AddTexture(std::shared_ptr<DiskTextureObject> texture)
    {
        m_Textures.push_back(texture);
    }

    void FillRemainingBindGroupEntry(std::vector<BindGroupEntry> & entries, int bindIndex)
    {
        auto & options = m_Pipeline->GetTextureBindGroupOptions();
        for (int i = bindIndex; i < constants::MAX_TEXTURE_SLOT; i++)
        {
            BindGroupEntry binding{};
            binding.binding = i;
            if (options[i].bindGroupType == BindGroupType::TEXTURE)
            {
                TextureView textureView = DiskTextureObject::EmptyTextureObject()->GetOrCreateTextureView();
                binding.textureView = textureView;
            }
            entries.push_back(binding);
        }
    }
};