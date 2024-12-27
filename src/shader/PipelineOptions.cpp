/*
#include "PipelineOptions.h"
#include "../base/Constants.h"

PipelineOptions PipelineOptions::POSITION = {
    Shader("resources/shaders/position.wgsl"),
    std::invoke([](){
        std::vector<VertexAttribute> v;
        v.push_back(VertexAttribCreator::PositionAttrib());
        return v;
    }),
    sizeof(Position),
    std::invoke([](){
        std::vector<BindGroupOptions> v;
        v.push_back({0, UniformBufferType::TIME, sizeof(float), false, "time"});
        v.push_back({1, UniformBufferType::VP, sizeof(ViewProjectionUniform), false, "vp"});
        v.push_back({2, UniformBufferType::MODEL, sizeof(ModelUniform), true, "model"});
        v.push_back({3, UniformBufferType::VEC4, sizeof(glm::vec4), true, "vec4"});
        return v;
    })
};

PipelineOptions PipelineOptions::POSITION_NORMAL = {
    Shader("resources/shaders/position_normal.wgsl"),
    std::invoke([](){
        std::vector<VertexAttribute> v;
        v.push_back(VertexAttribCreator::PositionAttrib());
        v.push_back(VertexAttribCreator::NormalAttrib());
        return v;
    }),
    sizeof(PositionNormal),
    std::invoke([](){
        std::vector<BindGroupOptions> v;
        v.push_back({0, UniformBufferType::TIME, sizeof(float), false, "time"});
        v.push_back({1, UniformBufferType::VP, sizeof(ViewProjectionUniform), false, "vp"});
        v.push_back({2, UniformBufferType::MODEL, sizeof(ModelUniform), true, "model"});
        v.push_back({3, UniformBufferType::VEC4, sizeof(glm::vec4), true, "vec4"});
        return v;
    })
};

PipelineOptions PipelineOptions::VERTEX_BASE = {
    Shader("resources/shaders/vertex_base.wgsl"),
    std::invoke([](){
        std::vector<VertexAttribute> v;
        v.push_back(VertexAttribCreator::PositionAttrib());
        v.push_back(VertexAttribCreator::NormalAttrib());
        v.push_back(VertexAttribCreator::UVAttrib());
        return v;
    }),
    sizeof(VertexBase),
    std::invoke([](){
        std::vector<BindGroupOptions> v;
        v.push_back({0, UniformBufferType::TIME, sizeof(float), false, "time"});
        v.push_back({1, UniformBufferType::VP, sizeof(ViewProjectionUniform), false, "vp"});
        v.push_back({2, UniformBufferType::MODEL, sizeof(ModelUniform), true, "model"});
        v.push_back({3, UniformBufferType::VEC4, sizeof(glm::vec4), true, "color"});
        v.push_back({4, UniformBufferType::POINTLIGHT, sizeof(PointLight) * constants::MAX_POINT_LIGHT, false, "pointlight"});
        v.push_back({5, UniformBufferType::COUNT, sizeof(CountUniform), false, "count"});
        return v;
    }),
    std::invoke([](){
        std::vector<TextureOptions> v;
        for (int i = 0; i < constants::MAX_TEXTURE_SLOT; i++)
        {
            uint8_t slot = i + 10;
            v.push_back({slot});
        }
        return v;
    }),
};


*/