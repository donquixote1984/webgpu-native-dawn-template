#include "structs.h.wgsl"

@group(0) @binding(0) var<uniform> uLights: Lights;
@group(0) @binding(1) var<uniform> csmLvl: i32;
// dynamic
@group(0) @binding(2) var<uniform> uModel: Model;


@vertex
fn vs_main(vertex: Vertex)->VertexOutput
{
    var csmMat: mat4x4f = uLights.directionalLights[0].csm[csmLvl];
    var position = vertex.position;
	var pos: vec4f = csmMat * uModel.modelMat * vec4f(position, 1.0); 


    var output : VertexOutput;
    output.position = pos;
    return output;
    
}

@fragment
fn fs_main(output: VertexOutput) ->@location(0) vec4f
{
    return vec4f(0.0, 0.0, 0.0, 1.0);
}