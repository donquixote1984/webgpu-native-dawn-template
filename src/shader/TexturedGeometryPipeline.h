#pragma once
#include "VertexBasePipeline.h"

class TexturedGeometryPipeline: public VertexBasePipeline
{
protected:

public:
    TexturedGeometryPipeline();
    virtual void CreateBindGroupLayout() override;
    virtual void CreatePipeline() override;
    
    static TexturedGeometryPipeline * Get()
    {
        static TexturedGeometryPipeline texturedGeometryBasePipeline;
        return &texturedGeometryBasePipeline;
    }
};