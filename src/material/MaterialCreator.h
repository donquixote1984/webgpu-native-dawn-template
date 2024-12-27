#pragma once
#include <memory>
#include <vector>
#include <unordered_map>
#include "TexturedMaterial.h"
#include "../textures/TextureLoader.h"
#include "../textures/DiskTextureObject.h"

class MaterialCreator
{
private:
    ObjectType m_Type;
    bool m_ReceiveShadow = false;
    std::unordered_map<TextureType, std::string> m_Textures;
    std::unordered_map<TextureType, std::shared_ptr<DiskTextureObject>> m_CachedTextureObjects;
public:
    static std::shared_ptr<MaterialCreator> Builder()
    {
        return std::make_shared<MaterialCreator>();
    }

    MaterialCreator * Type(ObjectType type)
    {
        m_Type = type;
        return this;
    }

    MaterialCreator * ReceiveShadow()
    {
        m_ReceiveShadow = true;
        return this;
    }

    MaterialCreator * AddTexture(TextureType type, const std::string &path) {
        m_Textures[type] = path;
        return this;
    }
    MaterialCreator * AddTexture(TextureType type, std::vector<uint8_t> data, int width, int height)
    {
        m_CachedTextureObjects[type] = std::make_shared<DiskTextureObject>(data, width, height);
        return this;
    }

    std::shared_ptr<TexturedMaterial> Build()
    {
        std::shared_ptr<TexturedMaterial> m = std::make_shared<TexturedMaterial>();
        
        for (auto & kv : m_Textures)
        {
            TextureType type = kv.first;
            // load texture from path by constructor
            std::shared_ptr<DiskTextureObject> texture = std::make_shared<DiskTextureObject>(kv.second);
            m.get()->AddTexture(type, texture);
        }

        for (auto & kv: m_CachedTextureObjects)
        {
            TextureType type = kv.first;
            std::shared_ptr<DiskTextureObject> texture = m_CachedTextureObjects[type];
            m.get()->AddTexture(type, texture);
        }

        if (m_ReceiveShadow)
        {
            m.get()->ReceiveShadow();
        }
        return m;
    }
};