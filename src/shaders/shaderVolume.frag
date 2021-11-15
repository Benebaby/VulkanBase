#version 450

struct Ray {
	vec3 origin;
	vec3 direction;
};


struct AABBox { 
    vec3 bounds[2];
};

layout(binding = 1) uniform sampler2D texSampler;

layout(origin_upper_left) in vec4 gl_FragCoord;
layout(location = 0) in vec3 fragColor;
layout(location = 1) in vec2 fragTexCoord;
layout(location = 2) in mat4 invModel;
layout(location = 6) in mat4 invView;
layout(location = 10) in mat4 invProj;
layout(location = 14) in vec2 size;

layout(location = 0) out vec4 outColor;

Ray calculateRay(vec2 offset) {
    vec2 pixelCenter = vec2(gl_FragCoord.xy) + offset;
	vec2 inUV = pixelCenter / size;
	vec2 d = inUV * 2.0 - 1.0;
	vec4 target = invProj * vec4(d.x, d.y, 1, 1) ;
    Ray ray;
    ray.origin = vec4(invModel * invView * vec4(0,0,0,1)).xyz;
    ray.direction = vec4(invModel * invView * vec4(normalize(target.xyz), 0)).xyz;
    return ray;
}

bool intersect(in Ray r, in AABBox box, out float tmin, out float tmax) { 
    float tymin, tymax, tzmin, tzmax, t; 
    vec3 invDir = (1.0 / r.direction);
    if(invDir.x < 0){
        tmin = (box.bounds[1].x - r.origin.x) * invDir.x;
        tmax = (box.bounds[0].x - r.origin.x) * invDir.x; 
    }else{
        tmin = (box.bounds[0].x - r.origin.x) * invDir.x;
        tmax = (box.bounds[1].x - r.origin.x) * invDir.x; 
    }
    if(invDir.y < 0){
        tymin = (box.bounds[1].y - r.origin.y) * invDir.y; 
        tymax = (box.bounds[0].y - r.origin.y) * invDir.y; 
    }else{
        tymin = (box.bounds[0].y - r.origin.y) * invDir.y; 
        tymax = (box.bounds[1].y - r.origin.y) * invDir.y;
    }
    if ((tmin > tymax) || (tymin > tmax)) 
        return false; 
    if (tymin > tmin) 
        tmin = tymin; 
    if (tymax < tmax) 
        tmax = tymax; 
    if(invDir.z < 0){
        tzmin = (box.bounds[1].z - r.origin.z) * invDir.z; 
        tzmax = (box.bounds[0].z - r.origin.z) * invDir.z; 
    }else{
        tzmin = (box.bounds[0].z - r.origin.z) * invDir.z; 
        tzmax = (box.bounds[1].z - r.origin.z) * invDir.z;
    }
    if ((tmin > tzmax) || (tzmin > tmax)) 
        return false; 
    if (tzmin > tmin) 
        tmin = tzmin; 
    if (tzmax < tmax) 
        tmax = tzmax; 
    t = tmin; 
    if (t < 0) { 
        t = tmax; 
        if (t < 0) 
            return false; 
    } 
    return true; 
} 

void main() {
    Ray ray = calculateRay(vec2(0.0));
    AABBox box; 
    box.bounds[0] = vec3(-0.5); 
    box.bounds[1] = vec3(0.5);
    float tmin = 0.0;
    float tmax = 0.0;
    bool intersects = intersect(ray, box, tmin, tmax);
    if(intersects){
        vec3 currentColor = vec3(0.0);
        for(float t = tmin; t < tmax ; t += 0.000976){
            vec2 uv = (ray.origin + t * ray.direction).xy + vec2(0.5);
            currentColor += texture(texSampler, uv).rgb * 0.003;
        }
        outColor = vec4(currentColor, 1.0);
    }else{
        outColor = vec4(vec3(0.0), 1.0);
    }
}