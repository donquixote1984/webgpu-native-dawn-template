#include "VertexBasePipeline.h"

VertexBasePipeline::VertexBasePipeline()
{
    // stride
    m_Stride = sizeof(VertexBase);
     // uniforms
    m_Attributes.push_back(VertexAttribCreator::PositionAttrib());
    m_Attributes.push_back(VertexAttribCreator::NormalAttrib());
    m_Attributes.push_back(VertexAttribCreator::UVAttrib());
}