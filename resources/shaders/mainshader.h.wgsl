
#include "shadow.h.wgsl"
#include "lights.h.wgsl"

fn CalculateColor(shadingPoint: ShadingPoint)-> vec4f
{
    let color = CalculateLights(shadingPoint);
    return color;
}