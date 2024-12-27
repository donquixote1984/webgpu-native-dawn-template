#pragma once
#include <webgpu/webgpu.hpp>
#include <string>

using namespace wgpu;
class TextureObject
{
protected:
    int m_Width;
    int m_Height;
    int m_Channels;

    Texture m_Texture = nullptr;

public:
    virtual TextureView GetOrCreateTextureView() = 0;
};