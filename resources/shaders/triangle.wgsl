

@group(0) @binding(0) var<uniform> uTime: f32;
@group(0) @binding(2) var<uniform> color: vec4f;

@vertex
fn vs_main(@location(0) position: vec3f) -> @builtin(position) vec4f {
	var offset = 0.3 * vec3f(cos(uTime), sin(uTime), 0.0);
	return vec4f(position + offset, 1.0);
}

@fragment
fn fs_main() -> @location(0) vec4f {
	return color;
}