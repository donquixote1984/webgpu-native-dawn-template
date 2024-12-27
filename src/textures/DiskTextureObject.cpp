#include "DiskTextureObject.h"
#include "TextureLoader.h"

DiskTextureObject::DiskTextureObject(const std::string &path)
{
    m_Texture = TextureLoader::LoadTexture(path, m_Width, m_Height, m_Channels);
    TextureViewDescriptor textureViewDesc;
    textureViewDesc.aspect = TextureAspect::All;
    textureViewDesc.baseArrayLayer = 0;
    textureViewDesc.arrayLayerCount = 1;
    textureViewDesc.baseMipLevel = 0;
    textureViewDesc.mipLevelCount = m_Texture.getMipLevelCount(); //textureDesc.mipLevelCount;
    textureViewDesc.dimension = TextureViewDimension::_2D;
    textureViewDesc.format = TextureFormat::RGBA8Unorm;
    m_TextureView = m_Texture.createView(textureViewDesc);
}
DiskTextureObject::DiskTextureObject(const std::vector<uint8_t> &data, unsigned int width, unsigned int height)
{
    m_Width = width;
    m_Height = height;
    m_Texture = TextureLoader::LoadTexture(data, width, height);
    TextureViewDescriptor textureViewDesc;
    textureViewDesc.aspect = TextureAspect::All;
    textureViewDesc.baseArrayLayer = 0;
    textureViewDesc.arrayLayerCount = 1;
    textureViewDesc.baseMipLevel = 0;
    textureViewDesc.mipLevelCount = m_Texture.getMipLevelCount(); //textureDesc.mipLevelCount;
    textureViewDesc.dimension = TextureViewDimension::_2D;
    textureViewDesc.format = TextureFormat::RGBA8Unorm;
    m_TextureView = m_Texture.createView(textureViewDesc);
}

DiskTextureObject::DiskTextureObject()
{
    // create empty texture. used for preserved bind group entry slot.
    TextureDescriptor textureDesc;
    textureDesc.dimension = TextureDimension::_2D;
    textureDesc.format = TextureFormat::RGBA8Unorm;
    textureDesc.size = { (unsigned int)1, (unsigned int)1, 1 };
    textureDesc.mipLevelCount = 1; // bit_width(std::max(textureDesc.size.width, textureDesc.size.height));
    textureDesc.sampleCount = 1;
    textureDesc.usage = TextureUsage::TextureBinding | TextureUsage::CopyDst;
    textureDesc.viewFormatCount = 0;
    textureDesc.viewFormats = nullptr;
    m_Texture= WGPUContext::device.createTexture(textureDesc);

    TextureViewDescriptor textureViewDesc;
    textureViewDesc.aspect = TextureAspect::All;
    textureViewDesc.baseArrayLayer = 0;
    textureViewDesc.arrayLayerCount = 1;
    textureViewDesc.baseMipLevel = 0;
    textureViewDesc.mipLevelCount = 1; //textureDesc.mipLevelCount;
    textureViewDesc.dimension = TextureViewDimension::_2D;
    textureViewDesc.format = TextureFormat::RGBA8Unorm;

    m_TextureView = m_Texture.createView(textureViewDesc);
}


void DiskTextureObject::GenerateMipmap()
{
    

}