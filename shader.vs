#version 410

in vec3 Position;

uniform mat4 gWorld;

void main()
{
	
    gl_Position = gWorld * vec4(0.03* Position, 1.0);
	
}
