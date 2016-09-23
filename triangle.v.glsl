layout(location=0) in vec3 vp;
layout(location=1) in vec3 col;
uniform mat4 mvp;
out vec3 color;

void main(void) {
	gl_Position = mvp * vec4(vp, 1.0);
	//gl_Position[2] += 0.8;

	color = col;
}
