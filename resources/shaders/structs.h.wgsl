const MAX_POINT_LIGHTS = 10;
const MAX_DIRECTIONAL_LIGHTS = 10;
const MAX_CSM_LVLS = 4;

const BINDING_SHADOW_MAP = 10;
struct ViewProjection
{
	view: mat4x4f,
	projection: mat4x4f,
    invview: mat4x4f,
    invprojection: mat4x4f,
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
    csmLvlDist: vec3f,
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

struct ShadingPoint {
    fragPos: vec3f,
    normal: vec3f,
    uv: vec2f,
};