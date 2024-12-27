#pragma once

#include "../enums/TextureType.h"
#include "../textures/DiskTextureObject.h"
#include "BaseMaterial.h"
#include "phases/SampleBackendRenderPhase.h"
#include "phases/TextureRenderPhase.h"
#include "../shadow/SceneShadowMapCSMTexture.h"

using namespace wgpu;

class Mesh;

class TexturedMaterial: public BaseMaterial
{
protected:
    
public:
    TexturedMaterial();
    ~TexturedMaterial();
    
    void AddTexture(TextureType type, std::shared_ptr<DiskTextureObject> texture)
    {
        auto lastPhase = GetLastScreenPhase();
        lastPhase.get()->AddTexture(type, texture);
    }
    
    void ReceiveShadow()
    {
        auto lastPhase = GetLastScreenPhase();
        lastPhase.get()->AddTexture(TextureType::SHADOW_MAP, SceneShadowMapCSMTexture::Get()->GetReaderTextureView());
        lastPhase.get()->ReceiveShadow();
    }
/*
    void SetBindGroupToRenderPass(RenderPassEncoder renderPass, int uniformIndex) override
    {
        renderPass.setBindGroup(0, this->GetUniformBindGroup(), this->GetDynamicOffsetCount(), this->GetDynamicOffsets(uniformIndex).data()); 
        renderPass.setBindGroup(1, this->GetTextureBindGroup(), 0, nullptr);
        renderPass.setBindGroup(2, this->GetSamplerBindGroup(), 0, nullptr);
    }
    */
};