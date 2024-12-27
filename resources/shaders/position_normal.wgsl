struct ViewProjection
{
	view: mat4x4f,
	projection: mat4x4f,
};
struct Model{
	model: mat4x4f,
};

struct Vertex {
    @location(0) position: vec3f, 
    @location(1) normal: vec3f,
};

struct VertexOutput {
    @builtin(position) position: vec4f,
    @location(0) normal: vec3f,
};

@group(0) @binding(0) var<uniform> uTime: f32;
@group(0) @binding(1) var<uniform> uViewProjection: ViewProjection;
@group(0) @binding(2) var<uniform> uModel: Model;


@vertex
fn vs_main(vertex: Vertex) -> VertexOutput {
//	var offset = 0.3 * vec3f(cos(uTime), sin(uTime), 0.0);
    var position = vertex.position;
	var pos: vec4f = uViewProjection.projection * uViewProjection.view * uModel.model * vec4f(position, 1.0); 
    var out: VertexOutput;
    out.position = pos;
    out.normal = vertex.normal;
	return out;
}

@fragment
fn fs_main(in: VertexOutput) -> @location(0) vec4f {
    let color = in.normal;
	return vec4f(color.x, color.y, color.z, 1.0);
}