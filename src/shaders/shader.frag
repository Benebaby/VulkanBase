#version 450

layout(binding = 1) uniform sampler2D texSampler;

layout(location = 0) in vec3 fragColor;
layout(location = 1) in vec2 fragTexCoord;

layout(location = 0) out vec4 outColor;

void main() {
    float color = texture(texSampler, fragTexCoord).r;
    outColor = vec4(color, 0.0, 0.0, 1.0);
}