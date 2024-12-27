#pragma once
#include "TextureObject.h"


class DiskTextureObject: public TextureObject
{
private:
    
    TextureView m_TextureView = nullptr;  // cache the texture view, does not change every frame
    DiskTextureObject();
public:
   
    DiskTextureObject(const std::string &path);
    DiskTextureObject(const std::vector<uint8_t> &data, unsigned int width, unsigned int height);
    ~DiskTextureObject() 
    {
        if (m_Texture != nullptr)
        {
            m_Texture.release();
            m_Texture.destroy();
            m_Texture = nullptr;
        };

        if (m_TextureView != nullptr)
        {
            m_TextureView.release();
            m_TextureView = nullptr;
        }
    }
    Texture GetTexture()
    {
        return m_Texture;
    }
    TextureView GetOrCreateTextureView() override
    {
        return m_TextureView;
    }

    static DiskTextureObject * EmptyTextureObject()
    {
        static DiskTextureObject t;
        return &t;
    }
    void GenerateMipmap();
};