#ifndef AQUASENSE_H
#define AQUASENSE_H

#define WIDTH  		1000
#define HEIGHT 		700

#define TITLE  		"AquaSense"
#define LINE_WIDTH 	2.0f

const char* VERTEX_SHADER_CODE = R"""(

#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec4 color;
layout (location = 2) in vec2 aTex;

out vec4 aColor;
out vec2 texCords;
uniform mat4 u_MVP;

void main() {
	gl_Position = u_MVP * vec4(position, 1.0f);
	texCords = aTex;
	aColor = color;
}

)""";

const char* FRAGMENT_SHADER_CODE = R"""(

#version 330 core

out vec4 FragColor;

in vec4 aColor;
in vec2 texCords;
uniform sampler2D textureIndex;

void main() {
	vec3 tt = texture(textureIndex, texCords).rgb;
	if (length(tt) == 0.0)
	{
		FragColor = aColor;
	}
	else
	{
		FragColor = texture(textureIndex, texCords);
	}
}


)""";

#endif