
@vertex
fn vs_main(vertex: Vertex) -> VertexOutput {
//	var offset = 0.3 * vec3f(cos(uTime), sin(uTime), 0.0);
    var position = vertex.position;
	var pos: vec4f = uViewProjection.projection * uViewProjection.view * uModel.modelMat * vec4f(position, 1.0); 
    var output : VertexOutput;

    output.position = pos;
    output.fragPos = uModel.modelMat * vec4f(position, 1.0);
    output.normal = (uModel.modelMat * vec4f(vertex.normal, 0.0));

    //output.normal = vec4f(vertex.normal, 1.0);
    output.uv = vertex.uv;
	return output;
}