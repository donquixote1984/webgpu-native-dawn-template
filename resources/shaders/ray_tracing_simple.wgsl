
const GEO_NUM = 10;
const SAMPLE_NUM = 128;
const MAX_BOUNCE = 32;
const ATTENUATION = 0.5f;


struct Vertex {
    @location(0) position: vec3f, 
    @location(1) normal: vec3f,
    @location(2) uv: vec2f,
};

struct VertexOutput {
    @builtin(position) position: vec4f,
    @location(0) fragPos: vec4f,
    @location(1) uv: vec2f,
    @location(2) ray: vec3f,
};

struct ViewProjection
{
	view: mat4x4f,
	projection: mat4x4f,
    invview: mat4x4f,
    invprojection: mat4x4f,
};

@group(0) @binding(0) var<uniform> uTime: f32;
@group(0) @binding(1) var<uniform> uCamPos: vec4f;
@group(0) @binding(2) var<uniform> uScreen: Screen;
@group(0) @binding(3) var<uniform> uViewProjection: ViewProjection;
@group(0) @binding(4) var<uniform> world: BVH;
@group(0) @binding(5) var<uniform> uHitableList: HitableList;

@group(1) @binding(0) var uScreenTexture0: texture_2d<f32>;
@group(1) @binding(1) var uScreenTexture1: texture_2d<f32>;
@group(1) @binding(2) var uScreenTexture2: texture_2d<f32>;
@group(1) @binding(3) var uScreenTexture3: texture_2d<f32>;
@group(1) @binding(4) var uScreenTexture4: texture_2d<f32>;
@group(1) @binding(5) var uScreenTexture5: texture_2d<f32>;
@group(1) @binding(6) var uScreenTexture6: texture_2d<f32>;
@group(1) @binding(7) var uScreenTexture7: texture_2d<f32>;
@group(1) @binding(8) var uScreenTexture8: texture_2d<f32>;
@group(1) @binding(9) var uScreenTexture9: texture_2d<f32>;


@group(2) @binding(0) var uTextureSampler: sampler;

#include "ray_tracing_struct.wgsl"
#include "ray_tracing_funcs.wgsl"
#include "ray_tracing_aabb.wgsl"

@vertex
fn vs_main(vertex: Vertex) -> VertexOutput {
//	var offset = 0.3 * vec3f(cos(uTime), sin(uTime), 0.0);
    var position = vertex.position;
	var pos: vec4f = vec4f(position, 1.0); 
    var output : VertexOutput;

    output.position = pos;
    output.uv = vertex.uv;
    output.fragPos = pos;
    output.ray = 
    (
        uViewProjection.invview * 
        vec4f((uViewProjection.invprojection * vec4f(vertex.position.xy, 0.0f, 1.0f)).xyz, 0.0f)
    ).xyz;
    // (inverse(view) * vec4((inverse(projection) * vec4(aPos.x, aPos.y, 0, 1.0)).xyz, 0.0)).xyz;

	return output;
}


@fragment
fn fs_main(in: VertexOutput) -> @location(0) vec4f {
    //let color = textureLoad(albedo, vec2i(uv * vec2f(textureDimensions(albedo))), 0).rgb;
    //let color = textureSample(uAlbedo, textureSampler, in.uv).rgb;

    //return vec4f(in.fragPos.xy, 0.0f, 1.0f);
    //return vec4f(uCamPos);

    var outputColor:vec3f = vec3f(0, 0, 0);
   
    var pixelUnit: f32 = 1.0f / f32(uScreen.width);
    //var hitRecord: HitRecord = sphere_hit_ray_out_hit_record(sphere, r, 0, 1);
    //var random_offset1 = random12(in.fragPos.x);
    var sampleNoise: vec4f = textureSample(uScreenTexture0, uTextureSampler, in.uv);

    for (var i: u32 = 0; i < SAMPLE_NUM; i++)
    {
        var offset: vec2f = (random12(f32(i)) * 2.0 - 1.0) * pixelUnit;
        var r: Ray;
        r.orig = uCamPos.xyz;
        r.dir = normalize(in.ray + vec3f(offset, 0.0f));
        r.time = 0.2 * random21(sampleNoise.xy * random12(f32(i + 126)));
        outputColor += ray_color_bvh(r, sampleNoise.xyz + random13(f32(i)));
    }
    
    outputColor /= SAMPLE_NUM;
    return vec4f(outputColor, 1.0);

  //  var hitableIndex: i32 = uBVH.bvhList[8].hitable;
 //   var hi: Hitable = uHitableList.hitableList[hitableIndex];
  //  return vec4f(hi.aabb.min);
    /*
    if (uBVH.bvhList[0].hitable== 2)
    {
        return vec4f(0.5, 0.0, 0.0, 1.0);
    } else {
        return vec4f(0.0, 0.0,0.0, 1.0f);
    }
    */
}