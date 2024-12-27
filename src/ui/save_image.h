#pragma once
#include <webgpu/webgpu.hpp>

#include <filesystem>
#include <string>
#include "stb/stb_image_write.h"

// Save a texture to disk
bool saveTexture(const std::filesystem::path path, wgpu::Device device, wgpu::Texture texture);

// Saving a texture view requires to blit it into another texture, because only textures can be retrieved
bool saveTextureView(const std::filesystem::path path, wgpu::Device device, wgpu::TextureView textureView, uint32_t width, uint32_t height);

std::filesystem::path resolvePath(int frame);

class FileRenderer {
public:
	FileRenderer(wgpu::Device device, uint32_t width, uint32_t height);
	bool render(const std::filesystem::path path, wgpu::TextureView textureView) const;
	bool render(const std::filesystem::path path, wgpu::Texture texture) const;

private:
	wgpu::Device m_device;
	uint32_t m_width;
	uint32_t m_height;
	wgpu::BindGroupLayout m_bindGroupLayout = nullptr;
	wgpu::RenderPassDescriptor m_renderPassDesc;
	wgpu::RenderPipeline m_pipeline = nullptr;
	wgpu::Texture m_renderTexture = nullptr;
	wgpu::TextureView m_renderTextureView = nullptr;
	wgpu::Buffer m_pixelBuffer = nullptr;
	wgpu::BufferDescriptor m_pixelBufferDesc;
};
