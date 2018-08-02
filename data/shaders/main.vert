#version 430 core
layout(location = 0) in vec3 vertCoord;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 normalCoord;

out vec2 texCoordOut;
out vec3 fragPos;
out vec3 normalPos;

uniform mat4 View, Model; // ModelViewProjection (Total matrix)

void main(){
    fragPos = vec3(Model * vec4(vertCoord, 1.0));
    normalPos = mat3(transpose(inverse(Model))) * normalCoord;
    texCoordOut = texCoord;

    gl_Position = View * vec4(fragPos, 1);
}
