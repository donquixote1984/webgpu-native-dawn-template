#pragma once
#include <glm/glm.hpp>
#include <algorithm>
#include <fmt/format.h>
#include "../base/Constants.h"

class AABB
{
public:
    glm::vec4 min;
    glm::vec4 max;
    
    AABB Merge(AABB bb2)
    {
        AABB aabb;
        aabb.min.x = std::min(min.x, bb2.min.x);
        aabb.min.y = std::min(min.y, bb2.min.y);
        aabb.min.z = std::min(min.z, bb2.min.z);

        aabb.max.x = std::max(max.x, bb2.max.x);
        aabb.max.y = std::max(max.y, bb2.max.y);
        aabb.max.z = std::max(max.z, bb2.max.z);

        return aabb;
    }
    void ExpandX(float t)
    {
        min.x -= t/2.0f;
        max.x += t/2.0f;
    }

    void ExpandY(float t)
    {
        min.y -= t/2.0f;
        max.y += t/2.0f;
    }
    void ExpandZ(float t)
    {
        min.z -= t/2.0f;
        max.z += t/2.0f;
    }

    void PadToMinimum()
    {
        if (max.x - min.x < constants::EXP)
        {
            ExpandX(constants::EXP);
        }
        if (max.y - min.y < constants::EXP)
        {
            ExpandY(constants::EXP);
        }

        if (max.z - min.z < constants::EXP)
        {
            ExpandZ(constants::EXP);
        }
    }

    std::string ToString()
    {
        return fmt::format("min x:{} y:{} z:{} ; max x:{}, y:{} z:{}", min.x, min.y, min.z, max.x, max.y, max.z);
    }
};