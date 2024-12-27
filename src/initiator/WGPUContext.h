#pragma once

#include <webgpu/webgpu.hpp>
#include <glfw/glfw3.h>
#include <unordered_map>
#include <vector>
#include "glfw3webgpu.h"
#include "../shader/Shader.h"
#include "../enums/ObjectType.h"


using namespace wgpu;

class PipelineOptions;
class WGPUContext
{
private:
    inline static Texture frameTexture;
public:
    const static size_t SCREEN_WIDTH = 640;
    const static size_t SCREEN_HEIGHT = 640;
    
    inline static Instance instance;
    inline static Device device;
    inline static Queue queue;
    inline static Surface surface;
    inline static SupportedLimits supportedLimits;
    inline static Limits limits;
    inline static TextureFormat surfaceFormat = wgpu::TextureFormat::Undefined;
    inline static std::unique_ptr<wgpu::ErrorCallback> errorCallbackHandle;


    static void Create(GLFWwindow *window);
    static void Release();

    static TextureView GetNextSurfaceTextureView();
    static RenderPipeline CreateRenderPipeline(Shader &shader, std::vector<VertexAttribute> vertexAttribs, uint16_t stride, BindGroupLayout * bindGroupLayouts, int bindGroupLayoutCounts, TextureFormat format = WGPUContext::surfaceFormat);
    static RenderPipeline CreateDepthOnlyRenderPipeline(Shader & shader, std::vector<VertexAttribute> vertexAttribs, uint16_t stride, BindGroupLayout * bindGroupLayouts, int bindGroupLayoutCount);
    static ComputePipeline CreateComputePipeline(Shader &shader,  BindGroupLayout * bindGroupLayouts);
    static ShaderModule CreateShaderModule(Shader shader);
    static RequiredLimits GetRequiredLimits(Adapter adapter);
    static RenderPassDescriptor CreateSurfaceRenderPassDesc(TextureView& depthView);
    static RenderPassDescriptor CreateTextureRenderPassDesc(TextureView& colorTextureView, TextureView& );
    static RenderPassEncoder CreateScreenRenderPass(Texture screenTexture, Texture depthTexture, CommandEncoder encoder);
    static Texture CreateScreenTexture();
    static Texture CreateScreenDepth();
    static TextureView CreateTextureView2D(Texture texture);
    static TextureView CreateDepthView2D(Texture depth);
    static RenderPassColorAttachment CreateColorAttachment(TextureView view);
    static RenderPassColorAttachment CreateSurfaceColorOverlayAttachment();
    static RenderPassDepthStencilAttachment CreateDepthAttachment(TextureView view);
    static RenderPassColorAttachment CreateSurfaceColorAttachment();

    static void ReleaseIfNotNull(BindGroup &);
    static void ReleaseIfNotNull(Texture &);
    static void ReleaseIfNotNull(TextureView &);
    static void ReleaseIfNotNull(CommandEncoder &encoder);
    static void ReleaseIfNotNull(Buffer &);
    static void ReleaseIfNotNull(ComputePipeline &);
    //static BindGroup CreateBindGroup(BindGroupLayout bindGroupLayout, size_t layoutCount);
};