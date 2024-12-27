
@group(0) @binding(0) var<uniform> uViewProjection: ViewProjection;
@group(0) @binding(1) var<uniform> uTime: f32;
@group(0) @binding(2) var<uniform> uLights: Lights;
@group(0) @binding(3) var<uniform> uCount: Count;
// dynamic
@group(0) @binding(4) var<uniform> uModel: Model;
@group(0) @binding(5) var<uniform> uColor: vec4f;

@group(1) @binding(0)                   var uAlbedo:    texture_2d<f32>;
@group(1) @binding(1)                   var uNormal:    texture_2d<f32>;
@group(1) @binding(2)                   var uRoughness: texture_2d<f32>;
@group(1) @binding(BINDING_SHADOW_MAP)  var uShadowMap: texture_depth_2d_array; 

@group(2) @binding(0)                   var uTextureSampler: sampler;
