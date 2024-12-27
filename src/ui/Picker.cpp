#include "Picker.h"

Picker::Picker()
{


    BufferDescriptor bufferDesc;
    bufferDesc.size = 4;
    bufferDesc.usage = BufferUsage::CopyDst | BufferUsage::MapRead;

    m_PickerReadBuffer = WGPUContext::device.createBuffer(bufferDesc);

/**
 * m_PickerUniformBuffer
 *  BufferDescriptor bufferDesc{};
        bufferDesc.size = size;
        bufferDesc.usage = BufferUsage::CopyDst | BufferUsage::Uniform;
        bufferDesc.mappedAtCreation = false;
        bufferDesc.label = "UniformBuffer";
        Buffer uniformBuffer = WGPUContext::device.createBuffer(bufferDesc);
        return uniformBuffer;->
 * **/
    int stride = sizeof(glm::vec4);
    m_PickerUniformBuffer = UniformBufferCreator::Create(constants::MAX_OBJ_NUM * stride);
    

    Shader shader("resources/shaders/picker.wgsl");
    std::vector<VertexAttribute> attrs;
    VertexAttribute va;
    va.shaderLocation = 0;
    va.format = VertexFormat::Float32x3;
    va.offset = 0;
    attrs.push_back(va);

    BindGroupLayoutDescriptor bindGroupLayoutDesc;
    bindGroupLayoutDesc.label = "pickerBindGroupLayout";
    BindGroupLayoutEntry bindGroupLayoutEntry;
    bindGroupLayoutDesc.entryCount = 1;
    bindGroupLayoutEntry.binding = 0;

    bindGroupLayoutEntry.buffer.type = BufferBindingType::Uniform;
    bindGroupLayoutEntry.buffer.minBindingSize = constants::MAX_OBJ_NUM * sizeof(glm::vec3);
    bindGroupLayoutEntry.buffer.hasDynamicOffset = false;

    bindGroupLayoutDesc.entries = &bindGroupLayoutEntry;
    bindGroupLayoutEntry.visibility = ShaderStage::Vertex | ShaderStage::Fragment;

    BindGroupLayout bindGroupLayout = WGPUContext::device.createBindGroupLayout(bindGroupLayoutDesc);

    BindGroupDescriptor bindGroupDescriptor;

    BindGroupEntry entry;
    entry.binding = 0;
    entry.buffer = m_PickerUniformBuffer;
    entry.offset = 0;
    entry.size = constants::MAX_OBJ_NUM * sizeof(glm::vec3);

    bindGroupDescriptor.label = "pickerBindGroup";
    bindGroupDescriptor.layout = bindGroupLayout;
    bindGroupDescriptor.entryCount = 1;
    bindGroupDescriptor.entries = &entry;

    m_PickerBindGroup = WGPUContext::device.createBindGroup(bindGroupDescriptor);
    m_PickerPipeline = WGPUContext::CreateRenderPipeline(shader, attrs, sizeof(glm::vec3), &bindGroupLayout, 1, TextureFormat::RGBA8Unorm);

    m_PickerPipeline.setLabel("pickerPipeline");
}