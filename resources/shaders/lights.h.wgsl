fn CalculatePointLights(shadingPoint: ShadingPoint) -> vec3f
{
    var color:vec3f = vec3f(0, 0, 0);
    for (var i = 0; i < uLights.pCount; i+=1)
    {
        var pointLight = uLights.pointLights[i];
        var lightDir: vec3f = (shadingPoint.fragPos- pointLight.position);
        var t = max(0, dot(shadingPoint.normal, normalize(-lightDir)));
        color += pointLight.color * t;
    }
    return color;
}


fn CalculateDirectionalLight(shadingPoint: ShadingPoint, dLight: DirectionalLight) -> vec3f 
{
    var color = vec3f(0.0f, 0.0f, 0.0f);
    var lightDir: vec3f = dLight.direction;

    let shadow = CalculateShadowDirectionalLight(shadingPoint, dLight);
    
    //return shadow;
    var t = max(0, dot(shadingPoint.normal, normalize(-lightDir)));
    color += dLight.color * t;
    return shadow;//vec3f(1.0f, 1.0f, 1.0f);
}
fn CalculateDirectionalLights(shadingPoint: ShadingPoint) -> vec3f
{
    var color:vec3f = vec3f(0, 0, 0);
    for (var i = 0; i < uLights.dCount; i+=1)
    {
        var directionalLight = uLights.directionalLights[i];
        color += CalculateDirectionalLight(shadingPoint, directionalLight);
    }
    return color;
}


fn CalculateLights(shadingPoint: ShadingPoint)->vec4f
{
    let color1 = CalculatePointLights(shadingPoint);
    let color2 = CalculateDirectionalLights(shadingPoint);
    return vec4f(color1 + color2, 1.0f);
}