

#include "mainshader.h.wgsl"

@fragment
fn fs_main(in: VertexOutput) -> @location(0) vec4f {
    let uv = in.uv;


    //let color = textureLoad(albedo, vec2i(uv * vec2f(textureDimensions(albedo))), 0).rgb;
    //let color = textureSample(uAlbedo, textureSampler, in.uv).rgb;

    var shadingPoint: ShadingPoint;
    shadingPoint.fragPos = in.fragPos.xyz;
    shadingPoint.normal = in.normal.xyz;
    shadingPoint.uv = in.uv;

    //var color1: vec3f = CalculatePointLight(in.fragPos.xyz, in.normal.xyz);
    //var color2: vec3f = CalculateDirectionalLight(in.fragPos.xyz, in.normal.xyz);
    let color = CalculateColor(shadingPoint);

    

    return color;
    //return vec4f(0.5, 0.5, 0.5, 1.0);
}