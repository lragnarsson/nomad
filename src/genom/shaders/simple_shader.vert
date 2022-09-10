#version 450

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;
layout(location = 2) in vec3 normal;
layout(location = 3) in vec2 uv;

layout(location = 0) out vec3 fragColor;

struct PointLight {
    vec4 position;
    vec4 color;
};

layout(set = 0, binding = 0) uniform GlobalUbo {
    mat4 projection;
    mat4 view;
    mat4 inverseView;
    vec4 ambientLightColor;
    PointLight pointLights[10]; // Update when changing
    int numLights;
} ubo;

layout(push_constant) uniform Push {
    mat4 modelMatrix;
    mat4 normalMatrix;
} push;

void main() {
    vec3 diffuseLight = ubo.ambientLightColor.xyz * ubo.ambientLightColor.w;
    vec3 specularLight = vec3(0.0);
    vec3 surfaceNormalWorld = normalize(mat3(push.normalMatrix) * normal);
    vec4 positionWorld = push.modelMatrix * vec4(position, 1.0);

    vec3 cameraPosWorld = ubo.inverseView[3].xyz;
    vec3 viewDirection = normalize(cameraPosWorld - positionWorld.xyz);

    for (int i = 0; i < ubo.numLights; i++) {
        PointLight light = ubo.pointLights[i];
        vec3 directionToLight = light.position.xyz - positionWorld.xyz;
        float attenuation = 1.0 / ( 0.01 * dot(directionToLight, directionToLight));
        directionToLight = normalize(directionToLight);

        float cosAngIncidence = max(dot(surfaceNormalWorld, directionToLight), 0);
        vec3 intensity = light.color.xyz * light.color.w * attenuation;
        diffuseLight += intensity * cosAngIncidence;

        // Specular Lighting
        vec3 halfAngle = normalize(directionToLight + viewDirection);
        float blinnTerm = dot(surfaceNormalWorld, halfAngle);
        blinnTerm = pow(blinnTerm, 256.0);
        specularLight += intensity * blinnTerm;
    }

    vec3 ambientLight = ubo.ambientLightColor.xyz * ubo.ambientLightColor.w;

    fragColor = diffuseLight + (ambientLight + specularLight) * color;
    gl_Position = ubo.projection * ubo.view * positionWorld;
}