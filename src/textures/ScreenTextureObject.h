#pragma once
#include "TextureObject.h"

class ScreenTextureObject: public TextureObject
{
public:
    ScreenTextureObject(){}
    ScreenTextureObject(Texture texture)
    {
        SetTexture(texture);
        m_Height = texture.getHeight();
        m_Width = texture.getWidth();
        m_Channels = 4;
    }

    bool HasTexture()
    {
        return m_Texture != nullptr;
    }
    void SetTexture(Texture texture)
    {
        m_Texture = texture;
    }
    TextureView GetOrCreateTextureView() override
    {
        // create every frame. since screentexture changed every frame.
        if (m_Texture == nullptr)
        {
            assert(0);
        }
        TextureViewDescriptor textureViewDesc;
        textureViewDesc.aspect = TextureAspect::All;
        textureViewDesc.baseArrayLayer = 0;
        textureViewDesc.arrayLayerCount = 1;
        textureViewDesc.baseMipLevel = 0;
        textureViewDesc.mipLevelCount = m_Texture.getMipLevelCount(); //textureDesc.mipLevelCount;
        textureViewDesc.dimension = TextureViewDimension::_2D;
        textureViewDesc.format = TextureFormat::RGBA8Unorm;
        return m_Texture.createView(textureViewDesc);
    }
};