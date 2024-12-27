
struct Vertex {
    @location(0) position: vec3f, 
    @location(1) normal: vec3f,
    @location(2) uv: vec2f,
};

struct VertexOutput {
    @builtin(position) position: vec4f,
    @location(1) uv: vec2f,
};
@group(0) @binding(0) var<uniform> uTime: f32;
@group(1) @binding(0) var uScreenTexture: texture_2d<f32>;
@group(2) @binding(0) var uTextureSampler: sampler;

@vertex
fn vs_main(vertex: Vertex) -> VertexOutput {
//	var offset = 0.3 * vec3f(cos(uTime), sin(uTime), 0.0);
    var position = vertex.position;
	var pos: vec4f = vec4f(position, 1.0); 
    var output : VertexOutput;

    output.position = pos;
    output.uv = vertex.uv;
	return output;
}


@fragment
fn fs_main(in: VertexOutput) -> @location(0) vec4f {
    //let color = textureLoad(albedo, vec2i(uv * vec2f(textureDimensions(albedo))), 0).rgb;
    //let color = textureSample(uAlbedo, textureSampler, in.uv).rgb;
    let color = textureSample(uScreenTexture, uTextureSampler, in.uv).rgb;
    return vec4f(color, 1.0f);
}