#version 450

layout (location = 0) in vec2 fragOffset;
layout (location = 0) out vec4 outColor;

struct PointLight {
    vec4 position;
    vec4 color;
    float attenuation;
};

layout(set = 0, binding = 0) uniform GlobalUbo {
    mat4 projection;
    mat4 view;
    mat4 inverseView;
    PointLight pointLights[10]; // Update when changing
    int numLights;
} ubo;

layout(push_constant) uniform Push {
    vec4 position;
    vec4 color;
    vec2 size;
} push;

void main() {
    outColor = vec4(push.color.xyz, 1.0);
}