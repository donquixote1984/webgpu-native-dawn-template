#pragma once
#include <webgpu/webgpu.hpp>
#include <glm/glm.hpp>
#include "../initiator/WGPUContext.h"
#include "../ui/Interactions.h"

using namespace wgpu;

/***
 * 
 * 
 * 
 * 
*/
class Geometry;
class RendererCommand
{
protected:
    CommandEncoder m_CommandEncoder = nullptr;
public:
    RendererCommand(){}
    ~RendererCommand()
    {
        WGPUContext::ReleaseIfNotNull(m_CommandEncoder);
    }
    void Begin()
    {
        CommandEncoderDescriptor desc = {};
        m_CommandEncoder = WGPUContext::device.createCommandEncoder(desc);
    }
    virtual void Render() = 0;

    CommandEncoder &GetCommand()
    {
        return m_CommandEncoder;
    }

    void UpdateModel(Geometry* geo);
    void UpdateModel(Geometry * geo, glm::mat4 modifier);
    virtual void PostCommandSubmit() {}
};