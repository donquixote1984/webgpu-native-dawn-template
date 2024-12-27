
struct VertexInput {
    @location(0) position: vec3f,
    @location(1) uv: vec2f,
}
@vertex
fn vs_main(input: VertexInput) -> @builtin(position) vec4f {
	return vec4f(input.position, 1.0);
}

@fragment
fn fs_main() -> @location(0) vec4f {
	return vec4f(0.0, 0.4, 1.0, 1.0);
}