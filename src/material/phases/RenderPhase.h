#pragma once

#include <webgpu/webgpu.hpp>
#include <functional>
#include <unordered_map>
#include <memory>
#include "../../enums/TextureType.h"
#include "../../shader/BasePipeline.h"
#include "../../initiator/WGPUContext.h"

#include "../../textures/DiskTextureObject.h"
#include "../../textures/ScreenTextureObject.h"

using namespace wgpu;
enum class RenderPhaseType
{
    BACKEND,
    SCREEN,
};

class Geometry;
class RenderPhase
{
protected:
    std::unordered_map<TextureType, std::shared_ptr<DiskTextureObject>> m_InputTextureObjects;
    std::unordered_map<TextureType, TextureView> m_ScreenTextureObjects;
    
    //TextureView colorTextureView = nullptr;
    //TextureView depthTextureView = nullptr;
    RenderPhaseType type = RenderPhaseType::SCREEN;
    //RenderPassDescriptor descriptor = {};
    BasePipeline *m_Pipeline = nullptr;

    BindGroup m_UniformBindGroup = nullptr;  // bind group can not create inside of pipeline , since the texture data need to read from external.
    BindGroup m_TextureBindGroup = nullptr;
    BindGroup m_SamplerBindGroup = nullptr;

public:
    ~RenderPhase();
    std::function<void(void **userdata, unsigned int numOfUserData)> preAction = nullptr;
    std::function<void(void **userdata, unsigned int numofUserData)> postAction = nullptr;
    
    virtual void CreateBindGroups() 
    {
        CreateUniformBindGroup();
    }
    void AddTexture(TextureType type, std::shared_ptr<DiskTextureObject> textureObject)
    {
        m_InputTextureObjects[type] = textureObject;
    }

    void AddTexture(TextureType type, TextureView texture)
    {
        m_ScreenTextureObjects[type] = texture;
    }
    

    virtual std::vector<uint32_t> GetDynamicOffsets(uint16_t index);
    uint8_t GetDynamicOffsetCount();
    void CreateUniformBindGroup();
};