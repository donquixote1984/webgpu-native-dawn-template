
struct ViewProjection
{
	view: mat4x4f,
	projection: mat4x4f,
};
struct Model{
	model: mat4x4f,
};
struct Vertex {
    @builtin(vertex_index) in_vertex_index: u32,
    @location(0) position: vec3f, 
    @location(1) normal: vec3f,
    @location(2) uv: vec2f,
};

struct VertexOutput {

    @builtin(position) position: vec4f,
    @location(0) pickColor: vec4f,
}
@group(0) @binding(0) var<uniform> uViewProjection: ViewProjection;
// dynamic
@group(0) @binding(1) var<uniform> uModel: Model;
@group(0) @binding(2) var<uniform> uPickColor: vec4f;


@vertex
fn vs_main(vertex: Vertex)->VertexOutput
{
    var position = vertex.position;
	var pos: vec4f = uViewProjection.projection * uViewProjection.view * uModel.model * vec4f(position, 1.0); 


    var output : VertexOutput;
    output.position = pos;
    output.pickColor = uPickColor;
    return output;
    
}

@fragment
fn fs_main(output: VertexOutput) ->@location(0) vec4f
{
    //return vec4f(1.0, 1.0, 0.0, 1.0);// pickUniforms.pickColor;
    return output.pickColor;
}