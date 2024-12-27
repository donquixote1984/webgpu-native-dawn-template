
fn GetCSMLayer(shadingPoint: ShadingPoint, dLight: DirectionalLight)-> i32
{
    let depth = shadingPoint.fragPos.z;
    var layer: i32 = -1;
    for (var i: i32 = 0; i < MAX_CSM_LVLS; i++)
    {
        if (depth <= dLight.csmLvlDist[i])
        {
            layer = i;
            break;
        }
    }

    if (layer == -1)
    {
        layer = MAX_CSM_LVLS - 1;
    }
    return layer;
}
fn CalculateShadowDirectionalLight(shadingPoint: ShadingPoint, dLight: DirectionalLight) -> vec3f
{
    let lvl = GetCSMLayer(shadingPoint, dLight);
    let shadowSpaceFragPos = dLight.csm[lvl] * vec4f(shadingPoint.fragPos, 1.0);
    var projCoords: vec3f = shadowSpaceFragPos.xyz / shadowSpaceFragPos.w;

    // vec3<f32>(shadowProjection.xy * vec2<f32>(0.5, -0.5) + vec2<f32>(0.5, 0.5), shadowProjection.z);

    //projCoords.x = projCoords.x * 0.5 + 0.5;
    //projCoords.y = projCoords.y * 0.5 + 0.5;

    // copied from https://github.com/damiano-massarelli/WebGPU-CSM/blob/master/src/renderer/forward.wgsl . , since UV coord is inverse direction of y space coord 
    projCoords = vec3f(projCoords.xy * vec2<f32>(0.5f, -0.5f) + vec2<f32>(0.5, 0.5), projCoords.z); 
    //projCoords = vec3f(projCoords.xyz * vec3<f32>(0.5f, -0.5f, 0.5f) + vec3<f32>(0.5, 0.5, 0.5)); 

    //projCoords.z = projCoords.z * -0.5 + 0.5;

    var currentDepth = projCoords.z;
   
    //projCoords.x = clamp(projCoords.x, 0.0f, 1.0f);
    //projCoords.y = clamp(projCoords.y, 0.0f, 1.0f);
    
    var closestDepth: f32 = textureSample(uShadowMap, uTextureSampler, projCoords.xy, lvl);
    var tileSize = vec2f(textureDimensions(uShadowMap));
    var tileSizeUnit = vec2f(1.0f, 1.0f) / tileSize;

    if (projCoords.z > 1.0)
    {
        currentDepth = 1.0;
    }
    let bias = 0.001;
    //var bias: f32 = max(0.001 * (1.0 - dot(shadingPoint.normal, normalize(-dLight.direction))), 0.0001);
    var shadow = 0.0f;
    var sampleFactor: f32= 3.0f;
   
    for (var x:f32 = -2; x <=2 ; x += 1)
    {
        for (var y: f32 = -2; y <=2; y+=1)
        {
            var pcf = textureSample(uShadowMap, uTextureSampler, projCoords.xy + vec2f(x*sampleFactor, y*sampleFactor) * tileSizeUnit.xy, lvl);
            shadow += select(1.0f, 0.0f, currentDepth - bias > pcf); //(currentDepth - bias > pcf ? 1.0 : 0.0);
        }
    }
    shadow /= 25;
    //var shadow = select(0.3f, 0.0f, currentDepth - 0.001> closestDepth);
    return vec3f(shadow);
}