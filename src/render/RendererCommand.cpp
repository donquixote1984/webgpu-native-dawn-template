#include "RendererCommand.h"
#include "../geometry/Geometry.h"

void RendererCommand::UpdateModel(Geometry* geo)
{
//    glm::mat4 model = geo->GetModelMat();
//    UniformBuffer *modelBuffer = ModelUniformBuffer::Get();
//    WGPUContext::queue.writeBuffer(modelBuffer->GetBuffer(), geo->GetUniformIndex() * modelBuffer->GetStride(), &model, modelBuffer->GetUnitSize());
    UpdateModel(geo, glm::mat4(1.0f));
}

void RendererCommand::UpdateModel(Geometry * geo, glm::mat4 modifier)
{
    glm::mat4 model = modifier * geo->GetModelMat();
    UniformBuffer *modelBuffer = ModelUniformBuffer::Get();
    WGPUContext::queue.writeBuffer(modelBuffer->GetBuffer(), geo->GetUniformIndex() * modelBuffer->GetStride(), &model, modelBuffer->GetUnitSize());
}