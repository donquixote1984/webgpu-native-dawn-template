#include "WGPUContext.h"
#include "../shader/PipelineOptions.h"

void WGPUContext::Create(GLFWwindow *window)
{

    WGPUInstanceDescriptor desc = {};
    desc.nextInChain = nullptr;

    // We create the instance using this descriptor
    Instance instance = wgpuCreateInstance(&desc);
    if (!instance) {
        std::cerr << "Could not initialize WebGPU!" << std::endl;
        assert(0);
    }


    WGPURequestAdapterOptions aOptions = {};
    aOptions.nextInChain = nullptr;
    if (window != nullptr) {
        WGPUContext::surface = glfwGetWGPUSurface(instance, window);
        aOptions.compatibleSurface = WGPUContext::surface;
    }

    WGPUContext::instance = instance;
    Adapter adapter = instance.requestAdapter(aOptions);
    //instance.release();

    WGPUDeviceDescriptor deviceDesc = {};
	deviceDesc.label = "My Device";
	deviceDesc.requiredFeatureCount = 0;
	deviceDesc.requiredLimits = nullptr;
	deviceDesc.defaultQueue.nextInChain = nullptr;
	deviceDesc.defaultQueue.label = "The default queue";
	deviceDesc.deviceLostCallback = [](WGPUDeviceLostReason reason, char const* message, void* /* pUserData */) {
		std::cout << "Device lost: reason " << reason;
		if (message) std::cout << " (" << message << ")";
		std::cout << std::endl;
        assert(0);
	};

	WGPUContext::device = adapter.requestDevice(deviceDesc);
    WGPUContext::errorCallbackHandle = WGPUContext::device.setUncapturedErrorCallback([](wgpu::ErrorType type, char const* message) {
		std::cout << "Uncaptured device error: type " << type;
		if (message) std::cout << " (" << message << ")";
		std::cout << std::endl;
        assert(0);
	});
    
    WGPUContext::queue = WGPUContext::device.getQueue();
    device.getLimits(&WGPUContext::supportedLimits);
    WGPUContext::limits = supportedLimits.limits;

    if (window != nullptr)
    {
        WGPUSurfaceConfiguration config = {};
        config.nextInChain = nullptr;
        config.width = WGPUContext::SCREEN_WIDTH;
        config.height = WGPUContext::SCREEN_HEIGHT;

        surfaceFormat = wgpuSurfaceGetPreferredFormat(surface, adapter);
        config.format = surfaceFormat;
        config.viewFormatCount = 0;
        config.viewFormats = nullptr;
        config.usage = WGPUTextureUsage_RenderAttachment;
        config.device = device;
        config.presentMode = WGPUPresentMode_Fifo;
        config.alphaMode = WGPUCompositeAlphaMode_Auto;
        wgpuSurfaceConfigure(surface, &config);

    }

    adapter.release();
}


void WGPUContext::Release()
{
    if (frameTexture != nullptr) {
        frameTexture.destroy();
        frameTexture.release();
    }
   
    queue.release();
    if (surface != nullptr) {
        surface.release();
        wgpuSurfaceUnconfigure(surface);
    }
    device.release();
    instance.release();
}

// per frame
TextureView WGPUContext::GetNextSurfaceTextureView()
{
    SurfaceTexture surfaceTexture;
    WGPUContext::surface.getCurrentTexture(&surfaceTexture);
    if (surfaceTexture.status != SurfaceGetCurrentTextureStatus::Success) {
		return nullptr;
	}
    frameTexture = surfaceTexture.texture;
    TextureViewDescriptor viewDescriptor;
	viewDescriptor.label = "Surface texture view";
	viewDescriptor.format = frameTexture.getFormat();
	viewDescriptor.dimension = TextureViewDimension::_2D;
	viewDescriptor.baseMipLevel = 0;
	viewDescriptor.mipLevelCount = 1;
	viewDescriptor.baseArrayLayer = 0;
	viewDescriptor.arrayLayerCount = 1;
	viewDescriptor.aspect = TextureAspect::All;
	TextureView targetView = frameTexture.createView(viewDescriptor);
    return targetView;
}




ShaderModule WGPUContext::CreateShaderModule(Shader shader)
{
    ShaderModuleDescriptor shaderDesc;

	// We use the extension mechanism to specify the WGSL part of the shader module descriptor
	ShaderModuleWGSLDescriptor shaderCodeDesc;
	// Set the chained struct's header
	shaderCodeDesc.chain.next = nullptr;
	shaderCodeDesc.chain.sType = SType::ShaderModuleWGSLDescriptor;
	// Connect the chain
	shaderDesc.nextInChain = &shaderCodeDesc.chain;
	shaderCodeDesc.code = shader.GetSource().c_str();
	ShaderModule shaderModule = WGPUContext::device.createShaderModule(shaderDesc);
    return shaderModule;
}

RenderPipeline WGPUContext::CreateDepthOnlyRenderPipeline(Shader & shader, std::vector<VertexAttribute> vertexAttribs, uint16_t stride, BindGroupLayout * bindGroupLayouts, int bindGroupLayoutCount)
{
    if (stride == 0)
    {
        std::cout << "create pipeline error" << std::endl;
        assert(0);
    }
    RenderPipelineDescriptor pipelineDesc{};
    pipelineDesc.nextInChain = nullptr;
    pipelineDesc.vertex.bufferCount = 1;
    pipelineDesc.vertex.buffers = nullptr;
    pipelineDesc.vertex.entryPoint = "vs_main";
    pipelineDesc.vertex.constantCount = 0;
    pipelineDesc.vertex.constants = nullptr;

    ShaderModule shaderModule = WGPUContext::CreateShaderModule(shader);
    pipelineDesc.vertex.module = shaderModule;

    VertexBufferLayout layout;
    layout.arrayStride = stride;
    layout.attributes = vertexAttribs.data();
    layout.stepMode = VertexStepMode::Vertex;
    layout.attributeCount = vertexAttribs.size();

    pipelineDesc.vertex.buffers = &layout;
    pipelineDesc.primitive.topology = wgpu::PrimitiveTopology::TriangleList;
    pipelineDesc.primitive.stripIndexFormat = wgpu::IndexFormat::Undefined;
    pipelineDesc.primitive.frontFace = wgpu::FrontFace::CCW;
    pipelineDesc.primitive.cullMode = wgpu::CullMode::None;

    // fragment 
    wgpu::FragmentState fragmentState;
    fragmentState.module = shaderModule;
    fragmentState.entryPoint = "fs_main";
    fragmentState.constantCount = 0;
    fragmentState.constants = nullptr;
    fragmentState.nextInChain = nullptr;

    pipelineDesc.fragment = &fragmentState;


    // depth texture
    DepthStencilState depthStencilState = Default;
    depthStencilState.depthCompare = CompareFunction::Less;
    depthStencilState.depthWriteEnabled = true;
    TextureFormat depthTextureFormat = TextureFormat::Depth32Float;
    depthStencilState.format = depthTextureFormat;
    depthStencilState.stencilReadMask = 0;
	depthStencilState.stencilWriteMask = 0;


    PipelineLayoutDescriptor layoutDesc;

    // 0 for matrixs and variables;
    // 1 for textures;
	layoutDesc.bindGroupLayoutCount = bindGroupLayoutCount;

    layoutDesc.bindGroupLayouts = (WGPUBindGroupLayout*)bindGroupLayouts;
    PipelineLayout pipelineLayout = device.createPipelineLayout(layoutDesc);
    pipelineDesc.layout = pipelineLayout;
    pipelineDesc.depthStencil = &depthStencilState;
    
    pipelineDesc.multisample.count = 1;
	pipelineDesc.multisample.mask = ~0u;
	pipelineDesc.multisample.alphaToCoverageEnabled = false;


    return WGPUContext::device.createRenderPipeline(pipelineDesc);
}


ComputePipeline WGPUContext::CreateComputePipeline(Shader & shader, BindGroupLayout * bindGroupLayouts)
{
    ShaderModule shaderModule =  WGPUContext::CreateShaderModule(shader);
    ComputePipelineDescriptor computePipelineDesc;
    PipelineLayoutDescriptor pipelineLayoutDesc;
    pipelineLayoutDesc.bindGroupLayoutCount = 1;
    pipelineLayoutDesc.bindGroupLayouts = (WGPUBindGroupLayout*)bindGroupLayouts;
    PipelineLayout pipelineLayout = device.createPipelineLayout(pipelineLayoutDesc);
    computePipelineDesc.compute.constantCount = 0;
    computePipelineDesc.compute.constants = nullptr;
    computePipelineDesc.compute.entryPoint = "compute";
    computePipelineDesc.compute.module = shader.GetShaderModule();
    computePipelineDesc.layout = pipelineLayout;
    WGPUContext::device.createComputePipeline(computePipelineDesc);
    pipelineLayout.release();
}

RenderPipeline WGPUContext::CreateRenderPipeline(Shader &shader, std::vector<VertexAttribute> vertexAttribs, uint16_t stride, BindGroupLayout * bindGroupLayouts, int bindGroupLayoutCount, TextureFormat colorFormat)
{
    if (stride == 0)
    {
        std::cout << "create pipeline error" << std::endl;
        assert(0);
    }
    RenderPipelineDescriptor pipelineDesc{};
    pipelineDesc.nextInChain = nullptr;
    pipelineDesc.vertex.bufferCount = 1;
    pipelineDesc.vertex.buffers = nullptr;
    pipelineDesc.vertex.entryPoint = "vs_main";
    pipelineDesc.vertex.constantCount = 0;
    pipelineDesc.vertex.constants = nullptr;

    ShaderModule shaderModule = WGPUContext::CreateShaderModule(shader);
    pipelineDesc.vertex.module = shaderModule;

    VertexBufferLayout layout;
    layout.arrayStride = stride;
    layout.attributes = vertexAttribs.data();
    layout.stepMode = VertexStepMode::Vertex;
    layout.attributeCount = vertexAttribs.size();

    pipelineDesc.vertex.buffers = &layout;
    pipelineDesc.primitive.topology = wgpu::PrimitiveTopology::TriangleList;
    pipelineDesc.primitive.stripIndexFormat = wgpu::IndexFormat::Undefined;
    pipelineDesc.primitive.frontFace = wgpu::FrontFace::CCW;
    pipelineDesc.primitive.cullMode = wgpu::CullMode::None;

    // fragment 
    wgpu::FragmentState fragmentState;
    fragmentState.module = shaderModule;
    fragmentState.entryPoint = "fs_main";
    fragmentState.constantCount = 0;
    fragmentState.constants = nullptr;
    fragmentState.nextInChain = nullptr;

    pipelineDesc.fragment = &fragmentState;

    // color
    BlendState blendState;
    ColorTargetState colorTarget;
    colorTarget.blend = &blendState;
    colorTarget.writeMask = wgpu::ColorWriteMask::All;
    colorTarget.format = colorFormat;
    fragmentState.targetCount = 1;
    fragmentState.targets = &colorTarget;

    blendState.color.srcFactor = wgpu::BlendFactor::SrcAlpha;
    blendState.color.dstFactor = wgpu::BlendFactor::OneMinusSrcAlpha;
    blendState.color.operation = wgpu::BlendOperation::Add;
	blendState.alpha.srcFactor = wgpu::BlendFactor::Zero;
	blendState.alpha.dstFactor = wgpu::BlendFactor::One;
	blendState.alpha.operation = wgpu::BlendOperation::Add;
    pipelineDesc.multisample.count = 1;
    pipelineDesc.multisample.mask = ~0u;
	pipelineDesc.multisample.alphaToCoverageEnabled = false;


    // depth texture
    DepthStencilState depthStencilState = Default;
    depthStencilState.depthCompare = CompareFunction::Less;
    depthStencilState.depthWriteEnabled = true;
    TextureFormat depthTextureFormat = TextureFormat::Depth32Float;
    depthStencilState.format = depthTextureFormat;
    depthStencilState.stencilReadMask = 0;
	depthStencilState.stencilWriteMask = 0;


    PipelineLayoutDescriptor layoutDesc;

    // 0 for matrixs and variables;
    // 1 for textures;
	layoutDesc.bindGroupLayoutCount = bindGroupLayoutCount;

    layoutDesc.bindGroupLayouts = (WGPUBindGroupLayout*)bindGroupLayouts;
    PipelineLayout pipelineLayout = device.createPipelineLayout(layoutDesc);
    pipelineDesc.layout = pipelineLayout;
    pipelineDesc.depthStencil = &depthStencilState;
    
    pipelineDesc.multisample.count = 1;
	pipelineDesc.multisample.mask = ~0u;
	pipelineDesc.multisample.alphaToCoverageEnabled = false;

    return WGPUContext::device.createRenderPipeline(pipelineDesc);
}

RequiredLimits WGPUContext::GetRequiredLimits(Adapter adapter)
{
    SupportedLimits supportedLimits;
    adapter.getLimits(&supportedLimits);

    RequiredLimits requiredLimits = Default;

    // We use at most 1 vertex attribute for now
    //requiredLimits.limits.maxVertexAttributes = 1;
    // We should also tell that we use 1 vertex buffers
    //requiredLimits.limits.maxVertexBuffers = 1;
    // Maximum size of a buffer is 6 vertices of 2 float each
    //requiredLimits.limits.maxBufferSize = 8 * 3 * sizeof(float);
    // Maximum stride between 2 consecutive vertices in the vertex buffer
    //requiredLimits.limits.maxVertexBufferArrayStride = 3 * sizeof(float);
    
    return requiredLimits;
}

RenderPassDescriptor WGPUContext::CreateSurfaceRenderPassDesc(TextureView &depthView)
{

    RenderPassDescriptor renderpassDesc = {};
    renderpassDesc.nextInChain = nullptr;
    renderpassDesc.colorAttachmentCount = 1;
    return renderpassDesc;
}

RenderPassEncoder WGPUContext::CreateScreenRenderPass(Texture screenTexture, Texture depthTexture, CommandEncoder encoder)
{
    RenderPassDescriptor renderPassDesc = {};
    renderPassDesc.nextInChain = nullptr;
    renderPassDesc.colorAttachmentCount = 1;

    TextureView depthView = WGPUContext::CreateDepthView2D(depthTexture);
    TextureView screenView = WGPUContext::CreateTextureView2D(screenTexture);
    auto att1 = WGPUContext::CreateColorAttachment(screenView);
    auto att2 = WGPUContext::CreateDepthAttachment(depthView);
    renderPassDesc.colorAttachments = &att1;
    renderPassDesc.depthStencilAttachment = &att2;
    RenderPassEncoder renderPass = encoder.beginRenderPass(renderPassDesc);

    depthView.release();
    screenView.release();
    return renderPass;
}


RenderPassColorAttachment WGPUContext::CreateSurfaceColorAttachment()
{
    TextureView targetView = WGPUContext::GetNextSurfaceTextureView();
    RenderPassColorAttachment renderpassColorAttachmentDesc = {};
    renderpassColorAttachmentDesc.view = targetView;
    renderpassColorAttachmentDesc.resolveTarget = nullptr;
    renderpassColorAttachmentDesc.loadOp = WGPULoadOp_Clear;
    renderpassColorAttachmentDesc.storeOp = WGPUStoreOp_Store;
    renderpassColorAttachmentDesc.clearValue = WGPUColor{ 0.0, 0.0, 0.0, 1.0 };
    renderpassColorAttachmentDesc.depthSlice = WGPU_DEPTH_SLICE_UNDEFINED;
    return renderpassColorAttachmentDesc;
}

RenderPassColorAttachment WGPUContext::CreateSurfaceColorOverlayAttachment()
{
    TextureView targetView = WGPUContext::GetNextSurfaceTextureView();
    RenderPassColorAttachment renderpassColorAttachmentDesc = {};
    renderpassColorAttachmentDesc.view = targetView;
    renderpassColorAttachmentDesc.resolveTarget = nullptr;
    renderpassColorAttachmentDesc.loadOp = WGPULoadOp_Load;
    renderpassColorAttachmentDesc.storeOp = WGPUStoreOp_Store;
    renderpassColorAttachmentDesc.clearValue = WGPUColor{ 0.0, 0.0, 0.0, 1.0 };
    renderpassColorAttachmentDesc.depthSlice = WGPU_DEPTH_SLICE_UNDEFINED;
    return renderpassColorAttachmentDesc;
}

Texture WGPUContext::CreateScreenTexture()
{
    TextureDescriptor textureDesc;
    textureDesc.size = {WGPUContext::SCREEN_WIDTH, WGPUContext::SCREEN_HEIGHT, 1};
    textureDesc.format = surfaceFormat;
    textureDesc.usage = TextureUsage::CopySrc | TextureUsage::RenderAttachment | TextureUsage::TextureBinding;
    textureDesc.sampleCount = 1;
    textureDesc.mipLevelCount = 1;
    return WGPUContext::device.createTexture(textureDesc);
}
Texture WGPUContext::CreateScreenDepth()
{
    TextureDescriptor depthDesc;
    depthDesc.size = {WGPUContext::SCREEN_WIDTH, WGPUContext::SCREEN_HEIGHT, 1};
    depthDesc.format = TextureFormat::Depth32Float;
    depthDesc.sampleCount = 1;
    depthDesc.mipLevelCount = 1;
    depthDesc.usage = TextureUsage::RenderAttachment | TextureUsage::TextureBinding;

    return WGPUContext::device.createTexture(depthDesc);
}

TextureView WGPUContext::CreateTextureView2D(Texture texture)
{
    TextureViewDescriptor textureViewDesc;
    textureViewDesc.aspect = TextureAspect::All;
    textureViewDesc.baseArrayLayer = 0;
    textureViewDesc.arrayLayerCount = 1;
    textureViewDesc.baseMipLevel = 0;
    textureViewDesc.mipLevelCount = 1; //textureDesc.mipLevelCount;
    textureViewDesc.dimension = TextureViewDimension::_2D;
    textureViewDesc.format = surfaceFormat;
    return texture.createView(textureViewDesc);
}
TextureView WGPUContext::CreateDepthView2D(Texture depth)
{
    TextureViewDescriptor depthTextureViewDesc;
    depthTextureViewDesc.aspect = TextureAspect::DepthOnly;
    depthTextureViewDesc.baseArrayLayer = 0;
    depthTextureViewDesc.arrayLayerCount = 1;
    depthTextureViewDesc.baseMipLevel = 0;
    depthTextureViewDesc.mipLevelCount = 1;
    depthTextureViewDesc.dimension = TextureViewDimension::_2D;
    depthTextureViewDesc.format = TextureFormat::Depth32Float;
    return depth.createView(depthTextureViewDesc);
}

RenderPassColorAttachment WGPUContext::CreateColorAttachment(TextureView colorView)
{
    RenderPassColorAttachment renderpassColorAttachmentDesc = {};
    renderpassColorAttachmentDesc.view = colorView;
    renderpassColorAttachmentDesc.resolveTarget = nullptr;
    renderpassColorAttachmentDesc.loadOp = WGPULoadOp_Clear;
    renderpassColorAttachmentDesc.storeOp = WGPUStoreOp_Store;
    renderpassColorAttachmentDesc.clearValue = WGPUColor{ 0.0, 0.0, 0.0, 1.0 };
    renderpassColorAttachmentDesc.depthSlice = WGPU_DEPTH_SLICE_UNDEFINED;
    return renderpassColorAttachmentDesc;
}

RenderPassDepthStencilAttachment WGPUContext::CreateDepthAttachment(TextureView depthView)
{
    RenderPassDepthStencilAttachment depthStencilAttachment;
    depthStencilAttachment.view = depthView;
    depthStencilAttachment.depthClearValue = 1.0f;
		// Operation settings comparable to the color attachment
    depthStencilAttachment.depthLoadOp = LoadOp::Clear;
    depthStencilAttachment.depthStoreOp = StoreOp::Store;
    // we could turn off writing to the depth buffer globally here
    depthStencilAttachment.depthReadOnly = false;
    depthStencilAttachment.stencilClearValue = 0;
    depthStencilAttachment.stencilLoadOp = LoadOp::Undefined;
    depthStencilAttachment.stencilStoreOp = StoreOp::Undefined;
    depthStencilAttachment.stencilReadOnly = true;
    return depthStencilAttachment;
}

void WGPUContext::ReleaseIfNotNull(BindGroup &group)
{
    if (group != nullptr)
    {
        group.release();
        group =nullptr;
    }
}
void WGPUContext::ReleaseIfNotNull(CommandEncoder &encoder)
{
    if (encoder != nullptr)
    {
        encoder.release();
        encoder =nullptr;
    }
}
void WGPUContext::ReleaseIfNotNull(Texture &t)
{
    if (t != nullptr)
    {
        t.release();
        t = nullptr;
    }
}
void WGPUContext::ReleaseIfNotNull(Buffer &buffer)
{
    if (buffer != nullptr)
    {
        buffer.release();
        buffer = nullptr;
    }
}
void WGPUContext::ReleaseIfNotNull(TextureView &tv)
{
    if (tv != nullptr)
    {
        tv.release();
        tv = nullptr;
    }
}

void WGPUContext::ReleaseIfNotNull(ComputePipeline &p)
{
    if (p != nullptr)
    {
        p.release();
        p = nullptr;
    }
}