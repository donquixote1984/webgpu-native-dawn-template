#pragma once
namespace constants
{
    const uint16_t MAX_OBJ_NUM = 100;
    const uint8_t MAX_POINT_LIGHT = 10;
    const uint8_t MAX_CSM_LVL = 4;
    const uint16_t MAX_BVH_SIZE = 200;
    const uint16_t MAX_HITABLE_SIZE = 64;
    const uint8_t MAX_DIRECTIONAL_LIGHT = 10;

    const uint8_t MAX_TEXTURE_SLOT = 10;
    const uint8_t BINDING_SHADOW_MAP = MAX_TEXTURE_SLOT;

    const float EXP = 1e-5;
}