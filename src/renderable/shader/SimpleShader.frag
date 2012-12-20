#version 330 core

smooth in vec4 fColor;

out vec4 color;

in vec2 UV;

smooth in vec3 vNormal;
smooth in vec3 vWorldPos; 
smooth in vec3 eyePos; 
smooth in vec3 vLightDir;
smooth in vec3 fragColor; 

uniform vec3 ambientCol;

uniform vec3 diffusePos;
uniform vec3 diffuseCol;
uniform vec3 diffuseDir;

uniform sampler2D textureSampler;

#include "/home/jacob/git/EDOP/src/renderable/shader/PointLight.frag"

struct simpleCont {
    vec3 pos; 
    vec3 col;
};

uniform Lights {
    simpleCont cont[32];
} lights;

uniform int LightsCount;

void main() {
    vec4 temp = vec4(texture2D( textureSampler, UV ).rgb, 0) - vec4(1);
    temp += vec4(ambientCol, 1);
    
    vec3 vNormalized = normalize(vNormal);;
    for(int i = 0; i<LightsCount; i++) {
        temp += vec4(fragColor, 0.2) * getPointLightColor(
            PointLight(lights.cont[i].col, lights.cont[i].pos, 10, 15, 0.05, 0.5)
            , vWorldPos, vNormalized);
    }
    
    color = temp;
}