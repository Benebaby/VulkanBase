#version 450

layout(binding = 1) uniform sampler2D texSampler;

layout(location = 0) in vec3 fragColor;
layout(location = 1) in vec2 fragTexCoord;

layout(location = 0) out vec4 outColor;

void main() {
    float value = texture(texSampler, fragTexCoord).r - 0.1 * (1.0/0.9);
    if(value < 0.4)
        outColor = vec4(vec3(0, value, 0), 1.0);
    else if(value >= 0.4 && value < 0.7)
        outColor = vec4(vec3(0, 0, value), 1.0);
    else if(value >= 0.7)
        outColor = vec4(vec3(value, 0, 0), 1.0);
    else
        outColor = vec4(vec3(value), 1.0);
}