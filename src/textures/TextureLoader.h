#pragma once

#include "stb/stb_image.h"
#include <string>
#include <vector>
#include <webgpu/webgpu.hpp>
#include "../initiator/WGPUContext.h"
#include "../utils/utils.h"

using namespace wgpu;
class TextureLoader
{
private:
    static void GenerateMipMap(Texture texture, Extent3D textureSize, uint32_t mipLevelCount, const unsigned char * originalPixelData)
    {
        Extent3D currentMipLevelSize = textureSize;
        std::vector<uint8_t> previousLevelPixels;
        Extent3D previousMipLevelSize;
        for (int level = 0; level < mipLevelCount; level++)
        {
            std::vector<uint8_t> pixels(4 * currentMipLevelSize.width * currentMipLevelSize.height);
            if (level == 0)
            {
                memcpy(pixels.data(), originalPixelData, pixels.size());
            }
            else
            {
                for (uint32_t i = 0; i < currentMipLevelSize.width; i++)
                {
                    for (uint32_t j = 0; j < currentMipLevelSize.height; j++)
                    {
                        uint32_t currentPixelIndex = 4 * (j * currentMipLevelSize.width + i);
                        unsigned char *p = &pixels[currentPixelIndex];

                        unsigned char * p00 = &previousLevelPixels[4 * ((2 * j + 0) * previousMipLevelSize.width + (2 * i + 0))];
                        unsigned char * p01 = &previousLevelPixels[4 * ((2 * j + 0) * previousMipLevelSize.width + (2 * i + 1))];
                        unsigned char * p10 = &previousLevelPixels[4 * ((2 * j + 1) * previousMipLevelSize.width + (2 * i + 0))];
                        unsigned char * p11 = &previousLevelPixels[4 * ((2 * j + 1) * previousMipLevelSize.width + (2 * i + 1))];

                        p[0] = (p00[0] + p01[0] + p10[0] + p11[0]) / 4;
					    p[1] = (p00[1] + p01[1] + p10[1] + p11[1]) / 4;
					    p[2] = (p00[2] + p01[2] + p10[2] + p11[2]) / 4;
					    p[3] = (p00[3] + p01[3] + p10[3] + p11[3]) / 4;
                    }
                }
            } 

            ImageCopyTexture destination;
	        destination.texture = texture;
	        destination.origin = { 0, 0, 0 };
	        destination.aspect = TextureAspect::All;
            destination.mipLevel = level;
            TextureDataLayout source;
	        source.offset = 0;
            source.bytesPerRow = 4 * currentMipLevelSize.width;
		    source.rowsPerImage = currentMipLevelSize.height;

            WGPUContext::queue.writeTexture(destination, pixels.data(), pixels.size(), source, currentMipLevelSize);
            // std::cout << currentMipLevelSize.width << std::endl;
            previousLevelPixels = std::move(pixels);
            previousMipLevelSize = currentMipLevelSize;
            currentMipLevelSize.width /= 2;
		    currentMipLevelSize.height /= 2;
        }
    }

    
    static Texture LoadTexture(const uint8_t* pixelData, unsigned int datasize, unsigned int width, unsigned int height)
    {
        if (nullptr == pixelData) return nullptr;
        TextureDescriptor textureDesc;
	    textureDesc.dimension = TextureDimension::_2D;
	    textureDesc.format = TextureFormat::RGBA8Unorm;
        textureDesc.size = { (unsigned int)width, (unsigned int)height, 1 };
        textureDesc.mipLevelCount = util::bit_width(std::max(width, height)); // bit_width(std::max(textureDesc.size.width, textureDesc.size.height));
	    textureDesc.sampleCount = 1;
	    textureDesc.usage = TextureUsage::TextureBinding | TextureUsage::CopyDst;
	    textureDesc.viewFormatCount = 0;
	    textureDesc.viewFormats = nullptr;
	    Texture texture = WGPUContext::device.createTexture(textureDesc);

        //  WGPUContext::queue.writeTexture(destination, pixelData, datasize, source, textureDesc.size);

        GenerateMipMap(texture, textureDesc.size, textureDesc.mipLevelCount, pixelData);
        return texture;
    }

public:
    static Texture LoadTexture(const std::string &path, int &width, int &height, int &channels)
    {
        uint8_t* pixelData = stbi_load(path.c_str(), &width, &height, &channels, 4 /* force 4 channels */);
        Texture texture = LoadTexture(pixelData, 4 * width * height, width, height);
        stbi_image_free(pixelData);
        return texture;
    }

    static Texture LoadTexture(const std::vector<uint8_t> &data, unsigned int width, unsigned int height)
    {
         return LoadTexture(data.data(), (unsigned int)data.size(), width, height);
    }

};