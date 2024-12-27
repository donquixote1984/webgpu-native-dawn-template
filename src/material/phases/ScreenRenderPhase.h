#pragma once
#include "RenderPhase.h"
#include "../../sampler/SamplerObject.h"

class ScreenRenderPhase: public RenderPhase
{
protected:
    bool m_ReceiveShadow = false;
    RenderPassEncoder m_RenderPass;
    RenderPhaseType type = RenderPhaseType::SCREEN;
public:
    virtual void RenderByRenderPass(RenderPassEncoder &renderPass, void ** context) = 0;

    void ReceiveShadow()
    {
        m_ReceiveShadow = true;
    }

    void AppendTextureBindGroupEntryFixed(std::vector<BindGroupEntry> & entries, int slot, TextureType type)
    {
        BindGroupEntry binding{};
        binding.binding = slot;
        binding.textureView = m_ScreenTextureObjects[type];
        entries.push_back(binding);
    }

    void AppendTextureBindGroupEntry(std::vector<BindGroupEntry> & entries, int &textureIndex, TextureType type)
    {
        if (m_InputTextureObjects.find(type) != m_InputTextureObjects.end())
        {
            BindGroupEntry binding{};
            binding.binding = textureIndex++;
            binding.textureView = m_InputTextureObjects[type].get()->GetOrCreateTextureView();
            entries.push_back(binding);
        }

        if (m_ScreenTextureObjects.find(type) != m_ScreenTextureObjects.end())
        {
            BindGroupEntry binding{};
            binding.binding = textureIndex;
            binding.textureView = m_ScreenTextureObjects[type];
            entries.push_back(binding);
        }
    }


};