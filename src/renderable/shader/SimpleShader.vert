#version 330 core

layout(location = 0) in vec3 positionIN;
layout(location = 1) in vec3 normalIN;
//layout(location = 2) in vec3 colorIN;
layout(location = 2) in vec2 textureIN;

in vec3 position;
in vec3 normal;
in vec3 color; 

out vec2 UV;

smooth out vec3 vNormal;
smooth out vec3 vWorldPos; 
smooth out vec3 eyePos; 
smooth out vec3 vLightDir;
smooth out vec3 fragColor; 

uniform mat3 nM;
uniform mat4 M; 
uniform mat4 V;
uniform mat4 P; 

uniform vec4 ambientCol;

uniform vec3 diffusePos;
uniform vec4 diffuseCol;
uniform vec3 diffuseDir;

void main(){		
    vNormal = nM * normalIN;
    vec4 eyePosition = V * M * vec4(positionIN, 1);
    eyePos = eyePosition.xyz;
    
    gl_Position =  ((P * V * M) * vec4(positionIN,1));
    vec4 WorldPos = M * vec4(positionIN, 1);
    vWorldPos = WorldPos.xyz;
    fragColor = color;
    UV = textureIN;
}