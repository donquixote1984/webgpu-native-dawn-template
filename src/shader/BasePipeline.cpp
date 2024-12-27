#include "BasePipeline.h"




void BasePipeline::Create()
{
    CreateBindGroupLayout();
    CreatePipeline();
}