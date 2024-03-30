#shader vertex
#version 330 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec2 aTex;

out vec2 texCords;

void main() {
	gl_Position = position;
	texCords = aTex;
}

#shader fragment
#version 330 core

out vec4 FragColor;

in vec2 texCords;
uniform sampler2D tex0;

void main() {
	FragColor = texture(tex0, texCords);
}
