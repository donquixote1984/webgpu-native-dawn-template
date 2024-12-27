struct ViewProjection
{
	view: mat4x4f,
	projection: mat4x4f,
};
struct Model{
	model: mat4x4f,
};

@group(0) @binding(0) var<uniform> uTime: f32;
@group(0) @binding(1) var<uniform> uViewProjection: ViewProjection;
@group(0) @binding(2) var<uniform> uModel: Model;


@vertex
fn vs_main(@location(0) position: vec3f) -> @builtin(position) vec4f {
//	var offset = 0.3 * vec3f(cos(uTime), sin(uTime), 0.0);
	var pos: vec4f = uViewProjection.projection * uViewProjection.view * uModel.model * vec4f(position, 1.0); 
	return pos;
}

@fragment
fn fs_main() -> @location(0) vec4f {
	return vec4f(0.0, 0.2, 0.2, 1.0);
}