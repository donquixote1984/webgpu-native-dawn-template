
fn get_sphere_uv_on_point(sphere: Sphere, p: vec3f)->vec2f
{
    var theta = acos(-p.y);
    var phi = atan2(-p.z, p.x) + PI;

    var u = phi / (2 * PI);
    var v = theta / PI;
    return vec2f(u, v);
}

fn hit_sphere(center: vec3f, radius: f32, r: Ray)-> bool
{
    var oc: vec3f = center - r.orig;
    var a = dot(r.dir, r.dir);
    var b = -2.0 * dot(r.dir, oc);
    var c = dot(oc, oc) - radius * radius;
    var discriminant = b * b - 4 * a * c;
    return discriminant >= 0;
}

fn hit_sphere_t(center: vec3f, radius: f32, r: Ray)->f32
{
    var oc: vec3f = center - r.orig;
    var a = dot(r.dir, r.dir);
    var b = -2.0 * dot(r.dir, oc);
    var c = dot(oc, oc) - radius * radius;
    var discriminant = b * b - 4 * a * c;

    if (discriminant < 0)
    {
        return -1.0f;
    }
    return (-b - sqrt(discriminant) ) / (2.0*a);
}


fn hit_sphere_t_input_sphere(sphere: Sphere, r: Ray)->f32
{

    var current_center = sphere.center;
    var oc: vec3f = current_center - r.orig;
    var a = dot(r.dir, r.dir);
    var b = -2.0 * dot(r.dir, oc);
    var c = dot(oc, oc) - sphere.radius * sphere.radius;
    var discriminant = b * b - 4 * a * c;

    if (discriminant < 0)
    {
        return -1.0f;
    }
    return (-b - sqrt(discriminant) ) / (2.0*a);
}


fn sphere_hit_ray_out_hit_record(sphere: Sphere, r: Ray, tmin: f32, tmax: f32)-> HitRecord
{
    var current_center = sphere.center;

    var oc: vec3f = current_center - r.orig;
    var a = dot(r.dir, r.dir);
    var b = -2.0 * dot(r.dir, oc);
    var c = dot(oc, oc) - sphere.radius * sphere.radius;
    var discriminant = b * b - 4 * a * c;

    if (discriminant < 0)
    {
        return create_empty_hit_record();
    }

    var t: f32 = (-b - sqrt(discriminant) ) / (2.0*a);
    if (t <= tmin || t >=tmax)
    {
        t = (-b + sqrt(discriminant) ) / (2.0*a);

        if (t <= tmin || t >=tmax)
        {
            return create_empty_hit_record();
        }
    }

    var hitRecord: HitRecord;
    hitRecord.isHit = true;
    hitRecord.t = t;
    hitRecord.position = ray_pos_at_t(r, t);
    hitRecord.normal = normalize(hitRecord.position - current_center);
    hitRecord.frontFace = dot(r.dir, hitRecord.normal) < 0;
    hitRecord.normal = select(-hitRecord.normal,hitRecord.normal,hitRecord.frontFace);
    hitRecord.uv = get_sphere_uv_on_point(sphere, hitRecord.normal);
    return hitRecord;
}