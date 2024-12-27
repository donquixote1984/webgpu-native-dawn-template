fn hit_color_on_checker(ray: Ray, hitRecord: HitRecord)->vec3f
{
    var material: HitableMaterial = hitRecord.material;
    var x = i32(hitRecord.position.x * material.factor);
    var y = i32(hitRecord.position.y * material.factor);
    var z = i32(hitRecord.position.z * material.factor);
    var isEven: bool = false;
    if ((x + y + z) %2 == 0)
    {
        isEven = true;
    }
    return select(vec3f(1.0f, 1.0f, 1.0f), material.color.xyz, isEven); // isEven ? material.color : vec3f(0.0f, 0.0f, 0.0f);
}

fn hit_color_on_texture(ray: Ray, hitRecord: HitRecord)->vec3f
{
    var uv: vec2f = hitRecord.uv;
    return textureSampleLevel(uScreenTexture1, uTextureSampler, uv, 0).xyz * 1.0f;
}

fn hit_color_on_lambert(ray: Ray, hitRecord: HitRecord)->vec3f
{
    var cos_theta: f32 = dot (hitRecord.normal, normalize(ray.dir));
    var scatter_pdf: f32 =  0;
    if (cos_theta < 0.0f) {
        scatter_pdf = 0;
    } else {
        scatter_pdf = cos_theta / PI;
    }

    var pdf_value:f32 = 1.0f / (2.0 * PI);
    return hitRecord.material.color.xyz  * scatter_pdf / pdf_value;
}

fn hit_color_on_material(ray: Ray, hitRecord: HitRecord)->vec3f
{
    var material: HitableMaterial = hitRecord.material;
    if (material._type == MAT_CHECKER) {
        return hit_color_on_checker(ray, hitRecord);
    }

    if (material._type == MAT_TEXTURE) {
        return hit_color_on_texture(ray, hitRecord);
    }

    if (material._type == MAT_LAM) {
        return hit_color_on_lambert(ray, hitRecord);
    }

    return hitRecord.material.color.xyz;
}
