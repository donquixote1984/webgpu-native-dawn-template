#pragma once
#include <webgpu/webgpu.hpp>
#include <map>
#include <any>
#include "../base/BaseObject.h"

using namespace wgpu;

#include <glm/glm.hpp>
#include "../initiator/WGPUContext.h"
class Mesh: public BaseObject
{
private:
    bool m_Pickable = true;
    glm::vec4 pickId;
public:
    Mesh() {
    }

    bool IsPickable() {
        return m_Pickable;
    }
   

    //void Ready() override;
};

