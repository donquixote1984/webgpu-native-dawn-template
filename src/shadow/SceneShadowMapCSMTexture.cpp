#include "SceneShadowMapCSMTexture.h"
//https://arche.graphics/zh-hans/docs/tutorial-graphics/shadow-advance/

SceneShadowMapCSMTexture::SceneShadowMapCSMTexture()
{
    TextureDescriptor textureDesc;
    textureDesc.dimension = TextureDimension::_2D;
    textureDesc.format = TextureFormat::Depth32Float;
    textureDesc.usage = TextureUsage::RenderAttachment | TextureUsage::TextureBinding;
    textureDesc.sampleCount = 1;
    textureDesc.mipLevelCount = 1;
    unsigned int heightDimension = (constants::MAX_CSM_LVL + 1) * constants::MAX_DIRECTIONAL_LIGHT;
    textureDesc.size = {WGPUContext::SCREEN_WIDTH * 4, WGPUContext::SCREEN_WIDTH * 4, heightDimension}; // mulitple layer
    m_AssembledDepthTexture = WGPUContext::device.createTexture(textureDesc);
    CreateRenderTextureViews();
    CreateReaderTextureView();
}
SceneShadowMapCSMTexture::~SceneShadowMapCSMTexture()
{
    for (TextureView &tv: m_RenderTextureViews)
    {
        WGPUContext::ReleaseIfNotNull(tv);
    }
    WGPUContext::ReleaseIfNotNull(m_ReaderTextureView);
    WGPUContext::ReleaseIfNotNull(m_AssembledDepthTexture);
}

void SceneShadowMapCSMTexture::CreateReaderTextureView()
{
    TextureViewDescriptor depthTextureViewDesc;
    depthTextureViewDesc.aspect = TextureAspect::DepthOnly;
    depthTextureViewDesc.baseArrayLayer = 0;
    depthTextureViewDesc.arrayLayerCount = constants::MAX_CSM_LVL;
    depthTextureViewDesc.baseMipLevel = 0;
    depthTextureViewDesc.mipLevelCount = 1;
    depthTextureViewDesc.dimension = TextureViewDimension::_2DArray;
    depthTextureViewDesc.format = TextureFormat::Depth32Float;
    m_ReaderTextureView = m_AssembledDepthTexture.createView(depthTextureViewDesc);
}

void SceneShadowMapCSMTexture::CreateRenderTextureViews()
{
    for (int i = 0; i < constants::MAX_CSM_LVL; i++)
    {
        TextureViewDescriptor depthTextureViewDesc;
        depthTextureViewDesc.aspect = TextureAspect::DepthOnly;
        depthTextureViewDesc.baseArrayLayer = i;
        depthTextureViewDesc.arrayLayerCount = 1;
        depthTextureViewDesc.baseMipLevel = 0;
        depthTextureViewDesc.mipLevelCount = 1;
        depthTextureViewDesc.dimension = TextureViewDimension::_2DArray;
        depthTextureViewDesc.format = TextureFormat::Depth32Float;
        TextureView textureView = m_AssembledDepthTexture.createView(depthTextureViewDesc);
        m_RenderTextureViews.push_back(textureView);
    }
}