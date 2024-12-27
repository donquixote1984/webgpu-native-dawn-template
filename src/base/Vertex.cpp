#include "Vertex.h"


VertexDescriptor VertexDescriptor::POSITION = {
    ObjectType::POSITION,
    sizeof(Position)
};

VertexDescriptor VertexDescriptor::POSITION_NORMAL = {
    ObjectType::POSITION_NORMAL,
    sizeof(PositionNormal)
};

VertexDescriptor VertexDescriptor::VERTEX_BASE = {
    ObjectType::VERTEX_BASE,
    sizeof(VertexBase)
};

VertexDescriptor VertexDescriptor::VERTEX = {
    ObjectType::VERTEX,
    sizeof(Vertex)
};
