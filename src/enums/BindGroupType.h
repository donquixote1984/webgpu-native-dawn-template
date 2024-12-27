#pragma once
enum class BindGroupType
{
    BUFFER,
    TEXTURE,
    SAMPLER,
    DEPTH,
    DEPTH_ARRAY,

    NONE,
    STORAGE,
    READ_ONLY_STORAGE,
};