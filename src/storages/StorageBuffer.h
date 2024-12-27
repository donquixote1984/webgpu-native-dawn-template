#pragma once
#include <webgpu/webgpu.hpp>
#include "../initiator/WGPUContext.h"

using namespace wgpu;


class StorageBufferCreator
{
public:
    static BufferDescriptor CreateDesc(size_t size, std::string name, bool map)
    {
        BufferDescriptor bufferDesc{};
        bufferDesc.size = size;
        bufferDesc.nextInChain = nullptr;
        
        if (map) {
            bufferDesc.usage = BufferUsage::CopyDst | BufferUsage::MapRead;
        } else {
            bufferDesc.usage = BufferUsage::Storage | BufferUsage::CopyDst;
        }
        bufferDesc.label = name.c_str();
        return bufferDesc;
    }
};

class StorageBuffer
{
protected:
public:
    Buffer m_Buffer = nullptr;
    std::string name;
    StorageBuffer(){}
    ~StorageBuffer() {
        WGPUContext::ReleaseIfNotNull(m_Buffer);
    }
    StorageBuffer(Buffer b, std::string name): m_Buffer(b), name(name){}
    Buffer & GetBuffer()
    {
        return m_Buffer;
    }
    static BufferDescriptor CreateDesc(size_t t, std::string name)
    {
        BufferDescriptor bufferDesc = StorageBufferCreator::CreateDesc(t, name, false);
        return bufferDesc;
    }
    static BufferDescriptor CreateMapDesc(size_t t, std::string name)
    {
        BufferDescriptor bufferDesc = StorageBufferCreator::CreateDesc(t, name, true);
        return bufferDesc;
    }
};
