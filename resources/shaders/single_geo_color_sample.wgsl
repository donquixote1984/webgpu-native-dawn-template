const MAX_POINT_LIGHTS = 10;
const MAX_DIRECTIONAL_LIGHTS = 10;
const MAX_CSM_LVLS = 5;
struct ViewProjection
{
	view: mat4x4f,
	projection: mat4x4f,
};
struct Model{
	modelMat: mat4x4f,
};
struct PointLight
{
    color: vec3f,
    position: vec3f,
};

struct DirectionalLight
{
    color: vec3f,
    direction: vec3f,
    csm: array<mat4x4f, MAX_CSM_LVLS>,
};

struct Lights
{
    pCount: i32,
    dCount: i32,
    bak1: i32,
    bak2: i32,
    pointLights: array<PointLight, MAX_POINT_LIGHTS>,
    directionalLights: array<DirectionalLight, MAX_DIRECTIONAL_LIGHTS>,
};

struct Count
{
    pointLightCount: i32,
    directionalLightCount: i32,
}

struct Vertex {
    @location(0) position: vec3f, 
    @location(1) normal: vec3f,
    @location(2) uv: vec2f,
};

struct VertexOutput {
    @builtin(position) position: vec4f,
    @location(0) fragPos: vec4f,
    @location(1) normal: vec4f,
    @location(2) uv: vec2f,
};


@group(0) @binding(0) var<uniform> uViewProjection: ViewProjection;
@group(0) @binding(1) var<uniform> uTime: f32;
@group(0) @binding(2) var<uniform> uLights: Lights;
@group(0) @binding(3) var<uniform> uCount: Count;
// dynamic
@group(0) @binding(4) var<uniform> uModel: Model;
@group(0) @binding(5) var<uniform> uColor: vec4f;


@vertex
fn vs_main(vertex: Vertex) -> VertexOutput {
//	var offset = 0.3 * vec3f(cos(uTime), sin(uTime), 0.0);
    var position = vertex.position;
	var pos: vec4f = uViewProjection.projection * uViewProjection.view * uModel.modelMat * vec4f(position, 1.0); 
    var output : VertexOutput;

    output.position = pos;
    output.fragPos = uModel.modelMat * vec4f(position, 1.0);
    output.normal = vec4f(vertex.normal, 1.0);
    output.uv = vertex.uv;
	return output;
}

@fragment
fn fs_main(in: VertexOutput) -> @location(0) vec4f {
    //let color = textureLoad(albedo, vec2i(uv * vec2f(textureDimensions(albedo))), 0).rgb;
    //let color = textureSample(uAlbedo, textureSampler, in.uv).rgb;

    return vec4f(1.0f, 0.0f, 0.0f, 1.0f);
}