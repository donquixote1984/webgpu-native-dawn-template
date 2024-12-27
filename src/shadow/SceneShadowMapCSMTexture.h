#pragma once

#include <webgpu/webgpu.hpp>
#include "../initiator/WGPUContext.h"
#include "../base/Constants.h"

using namespace wgpu;
class SceneShadowMapCSMTexture
{
private:
    Texture m_AssembledDepthTexture = nullptr;
    std::vector<TextureView> m_RenderTextureViews;
    TextureView m_ReaderTextureView = nullptr;
    SceneShadowMapCSMTexture();
public:
    ~SceneShadowMapCSMTexture();
    void CreateReaderTextureView();
    void CreateRenderTextureViews();

    static SceneShadowMapCSMTexture *Get()
    {
        static SceneShadowMapCSMTexture sceneShadowMapCSMTexture;
        return &sceneShadowMapCSMTexture;
    }
    TextureView GetReaderTextureView()
    {
        return m_ReaderTextureView;
    }
    TextureView GetRenderTextureView(int index)
    {
        return m_RenderTextureViews[index];
    }
};