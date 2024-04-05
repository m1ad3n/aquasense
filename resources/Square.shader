#shader vertex
#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 aTex;

out vec2 texCords;
uniform mat4 cameraMat;

void main() {
	gl_Position = cameraMat * vec4(position, 1.0f);
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
